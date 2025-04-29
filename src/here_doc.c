/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:22:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/29 16:57:59 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child(t_mini *ms, char *file, int quotes, int *fd, int n);
static int	heredoc_free(t_mini *ms, char *file, int *fd, int exit);
static char	*check_quotes(char *file, int *a);
static void	update_fds(t_mini *ms, int n, int fd);

void	here_doc(t_mini *ms, char *file, int n)
{
	int		fd[2];
	int		quotes;
	pid_t	pid;
	int		sts;
	
	file = check_quotes(file, &quotes);
	pipe(fd);
	pid = fork();
	ms->childrun = 1;
	signal(SIGINT, sigint_child);
	if (pid == 0)
		heredoc_child(ms, file, quotes, fd, n);
	free(file);
	close(fd[1]);
	waitpid(pid, &sts, 0);
	if (WIFSIGNALED(sts))
	{
		if (WTERMSIG(sts) == SIGINT)
			g_exit_status = 130;
	}
	else
		g_exit_status = WEXITSTATUS(sts);
	update_fds(ms, n, fd[0]);
}

static void	heredoc_child(t_mini *ms, char *file, int quotes, int *fd, int n)
{
	char	buff[LINE_MAX];
	char	*s;
	int		r;

	s = NULL;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		ft_putstr_fd("> ", 0);
		r = read(STDIN_FILENO, buff, LINE_MAX);
		buff[r] = '\0';
		if (r == 0)
		{
			ft_printf_fd(2, 
			"minishell: warning: here-document "
			"delimited by end-of-file (wanted `%s')\n", file);
			break ;
		}
		if (r < 0)
			exit(heredoc_free(ms, file, fd, n));
		if (ft_strncmp(file, buff, ft_strlen(file)) == 0)
			break ;
		if (!quotes)
			s = expand(ft_strdup(buff), ms, 0);
		write(fd[1], buff, ft_strlen(buff));
		if (s)
			free(s);
	}
	exit(heredoc_free(ms, file, fd, n));
}

static int heredoc_free(t_mini *ms, char *file, int *fd, int n)
{
	free(file);
	close(fd[1]);
	close(fd[0]);
	free_mem(ms->redirap);
	exec_free(ms, n, FREE_BASE | FREE_STRUCT | FREE_FDS | FREE_PIPES
			| FREE_CMD, 0);
	return (0);
}

static void	update_fds(t_mini *ms, int n, int fd)
{
	ms->childrun = 0;
	ms->cmd[n].input_fd = fd;
	if (ms->cmd[n].redirin != -1)
		close(ms->cmd[n].redirin);
	ms->cmd[n].redirin = fd;
}

static char	*check_quotes(char *file, int *quotes)
{
	char	*s;

	if (file[0] == '\"' || file[0] == '\'')
	{
		*quotes = 1;
		s = get_new_str(file);
		return (s);
	}
	*quotes = 0;
	return (ft_strdup(file));
}
