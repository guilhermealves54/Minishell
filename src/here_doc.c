/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:22:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/09 19:43:14 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child(t_mini *ms, char *file, int quotes, int *fd);
static int	heredoc_child_read(t_mini *ms, int r, char *file, int *fd);
static int	heredoc_free(t_mini *ms, char *file, int *fd);
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
		heredoc_child(ms, file, quotes, fd);
	free(file);
	close(fd[1]);
	waitpid(pid, &sts, 0);
	update_fds(ms, n, fd[0]);
}

static void	heredoc_child(t_mini *ms, char *file, int quotes, int *fd)
{
	char	buff[LINE_MAX];
	char	*s;
	int		r;

	s = NULL;
	signal(SIGINT, sigint_heredoc);
	while (1)
	{
		ft_putstr_fd("> ", 0);
		r = read(STDIN_FILENO, buff, LINE_MAX);
		buff[r] = '\0';
		if (heredoc_child_read(ms, r, file, fd)
			|| ft_strncmp(file, buff, ft_strlen(buff) -1) == 0)
			break ;
		if (!quotes)
		{
			s = expand(ft_strdup(buff), ms, 0);
			write(fd[1], s, ft_strlen(s));
		}
		else
			write(fd[1], buff, ft_strlen(buff));
		if (s)
			free(s);
	}
	exit(heredoc_free(ms, file, fd));
}

static int	heredoc_child_read(t_mini *ms, int r, char *file, int *fd)
{
	if (r == 0)
	{
		ft_printf_fd(2,
			"minishell: warning: here-document "
			"delimited by end-of-file (wanted `%s')\n", file);
		return (1);
	}
	if (r < 0)
		exit(heredoc_free(ms, file, fd));
	return (0);
}

static int	heredoc_free(t_mini *ms, char *file, int *fd)
{
	free(file);
	close(fd[1]);
	close(fd[0]);
	free_mem(ms->redirap);
	exec_free(ms, ms->pipes, FREE_BASE | FREE_STRUCT | FREE_FDS | FREE_PIPES
		| FREE_CMD | FREE_REDIR, 0);
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
