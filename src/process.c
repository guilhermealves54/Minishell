/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:24 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/15 17:37:17 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ex_builtin(t_mini *ms, int n);
static void	run_child(t_mini *ms, int pipes, int n, int i);
static void	get_exit_code(t_mini *ms, int proc);
static int	signal_sts(int sts);

void	fork_proc(t_mini *ms, int proc, int pipes)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (n < proc)
	{
		if (ms->cmd[n].builtin == 1)
			ms->exit_status = ex_builtin(ms, n);
		else
		{
			run_child(ms, pipes, n, i);
			i++;
		}
		n++;
	}
	close_pipes(ms, pipes);
	get_exit_code(ms, proc);
	exec_free(ms, pipes, FREE_STRUCT | FREE_CMD | FREE_FDS
		| FREE_PIDS, 1);
}

static int	ex_builtin(t_mini *ms, int n)
{
	if (ft_strcmp("echo", ms->cmd[n].cmd[0]) == 0)
		return (print_echo(ms->cmd[n].cmd), 0);
	else if (ft_strcmp("export", ms->cmd[n].cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("unset", ms->cmd[n].cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("pwd", ms->cmd[n].cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("cd", ms->cmd[n].cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("env", ms->cmd[n].cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("exit", ms->cmd[n].cmd[0]) == 0)
		return (1);
	return (1);
}

static void	run_child(t_mini *ms, int pipes, int n, int i)
{
	g_childrun = 1;
	ms->pid[i] = fork();
	if (ms->pid[i] < 0)
	{
		perror("Error: ");
		exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
				| FREE_FDS | FREE_PIPES | FREE_PIDS, 1));
	}
	if (ms->pid[i] == 0)
	{
		child_proc(ms, n, pipes);
	}
	g_childrun = 0;
}

static void	get_exit_code(t_mini *ms, int proc)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (n < proc)
	{
		if (ms->cmd[n].builtin == 0)
		{
			waitpid(ms->pid[i], &ms->cmd[n].sts, 0);
			if (WIFSIGNALED(ms->cmd[n].sts))
				ms->exit_status = signal_sts(ms->cmd[n].sts);
			else
				ms->exit_status = WEXITSTATUS(ms->cmd[n].sts);
			i++;
		}
		n++;
	}
}

static int	signal_sts(int sts)
{
	int	sig;

	sig = WTERMSIG(sts);
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		return (131);
	}
	if (sig == SIGINT)
		return (130);
	return (WEXITSTATUS(sts));
}
