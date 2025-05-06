/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:43:42 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/06 13:53:07 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_pipe(t_mini *ms, int n);
int			*crt_pid_arr(t_mini *ms, int pid_n, int pipes);
int			check_cmd(char *cmd);

int	**crt_pipes(t_mini *ms, int pipes)
{
	int	n;

	ms->fds = malloc(pipes * sizeof(int *));
	if (!ms->fds)
	{
		ft_printf_fd(2, "minishell: error allocating memory\n");
		exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT, 1));
	}
	n = 0;
	while (n < pipes)
	{
		open_pipe(ms, n);
		n++;
	}
	return (ms->fds);
}

static void	open_pipe(t_mini *ms, int n)
{
	ms->fds[n] = malloc(2 * sizeof(int));
	if (!ms->fds[n])
	{
		ft_printf_fd(2, "minishell: error allocating memory\n");
		exit(exec_free(ms, n, FREE_BASE | FREE_STRUCT | FREE_FDS, 1));
	}
	if (pipe(ms->fds[n]) == -1)
	{
		ft_printf_fd(2, "minishell: error allocating memory\n");
		exec_free(ms, n, FREE_PIPES, 1);
		exit(exec_free(ms, n + 1, FREE_BASE | FREE_STRUCT | FREE_FDS, 1));
	}
}

int	*crt_pid_arr(t_mini *ms, int pid_n, int pipes)
{
	int	*pid;

	pid = NULL;
	if (pid_n > 0)
	{
		pid = ft_calloc((pid_n), sizeof(int));
		if (!pid)
		{
			ft_printf_fd(2, "minishell: error allocating memory\n");
			exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
					| FREE_FDS | FREE_PIPES, 1));
		}
	}
	return (pid);
}

int	check_cmd(char *cmd)
{
	if (!cmd)
		return (-1);
	else if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("env", cmd) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd) == 0)
		return (1);
	else
		return (0);
}
