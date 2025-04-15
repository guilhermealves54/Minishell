/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/15 17:07:06 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_mini *ms, int n);

void	child_proc(t_mini *ms, int n, int pipes)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (access (ms->cmd[n].path, X_OK) != 0)
		ms->cmd[n].path = get_path(ms, n);
	if (!ms->cmd[n].path)
	{
		ft_printf_fd ("%s: command not found\n", ms->cmd[n].cmd[0]);
		exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD | FREE_FDS
				| FREE_PIPES | FREE_PIDS, 127));
	}
	dup2(ms->cmd[n].input_fd, STDIN_FILENO);
	dup2(ms->cmd[n].output_fd, STDOUT_FILENO);
	close_pipes(ms, pipes);
	execve (ms->cmd[n].path, ms->cmd[n].cmd, ms->envp);
	if (ms->cmd[n].cmd[0] != ms->cmd[n].path)
		free(ms->cmd->path);
	exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD | FREE_FDS
			| FREE_PIPES | FREE_PIDS, 1));
}

static char	*get_path(t_mini *ms, int n)
{
	char	*home;
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	home = ft_getenv("PATH", ms);
	if (!home)
		return (NULL);
	path = ft_split(home, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin_3(path[i], ms->cmd[n].cmd[0], '/');
		if (access(temp, X_OK) == 0)
			return (free_mem(path), temp);
		free(temp);
		i++;
	}
	return (free_mem(path), NULL);
}
