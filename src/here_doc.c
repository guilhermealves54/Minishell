/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:22:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/23 16:31:38 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_init(int *stdin_bk, char **file, int *fd, int *quotes);
static void	heredoc_signal(t_mini *ms, int *fd, int stdin_bk, char *file);
static char	*check_quotes(char *file, int **a);
static void	update_fds(t_mini *ms, int n, int *fd, char *file);

void	here_doc(t_mini *ms, char *file, int n)
{
	char	*s;
	int		fd[2];
	int		quotes;
	int		stdin_bk;

	heredoc_init(&stdin_bk, &file, fd, &quotes);
	while (1)
	{
		s = readline("> ");
		if (!s)
			return (heredoc_signal(ms, fd, stdin_bk, file));
		if (ft_strcmp(file, s) == 0)
		{
			free(s);
			break ;
		}
		if (!quotes)
			s = expand(s, ms);
		write(fd[1], s, ft_strlen(s));
		write(fd[1], "\n", 1);
		free(s);
	}
	close(stdin_bk);
	update_fds(ms, n, fd, file);
}

static void	heredoc_init(int *stdin_bk, char **file, int *fd, int *quotes)
{
	*stdin_bk = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	*file = check_quotes(*file, &quotes);
	pipe(fd);
}

static void	heredoc_signal(t_mini *ms, int *fd, int stdin_bk, char *file)
{
	if (g_childrun)
	{
		ms->exit_status = 130;
		close(fd[0]);
		close(fd[1]);
		free(file);
		setup_signals();
		g_childrun = 0;
		dup2(stdin_bk, STDIN_FILENO);
		close(stdin_bk);
		return ;
	}
	else
	{
		ft_printf_fd(2,
			"minishell: warning: here-document at line "
			"1 delimited by end-of-file (wanted `%s')\n", file);
		close(fd[0]);
		close(fd[1]);
		close(stdin_bk);
		free(file);
		setup_signals();
		return ;
	}
}

static void	update_fds(t_mini *ms, int n, int *fd, char *file)
{
	free(file);
	close(fd[1]);
	ms->cmd[n].input_fd = fd[0];
	if (ms->cmd[n].redirin != -1)
		close(ms->cmd[n].redirin);
	ms->cmd[n].redirin = *fd;
	setup_signals();
}

static char	*check_quotes(char *file, int **quotes)
{
	char	*s;

	if (file[0] == '\"' || file[0] == '\'')
	{
		**quotes = 1;
		s = get_new_str(file);
		return (s);
	}
	**quotes = 0;
	return (ft_strdup(file));
}
