/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:24 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/21 15:58:30 by ruida-si         ###   ########.fr       */
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
		if (ms->cmd[n].cmd)
		{
			if (ms->cmd[n].builtin == 1)
				ms->exit_status = ex_builtin(ms, n);
			else if (ms->cmd[n].cmd[0])
			{
				g_childrun = 1;
				run_child(ms, pipes, n, i);
				i++;
			}
		}
		n++;
	}
	close_pipes(ms, pipes);
	get_exit_code(ms, proc);
	g_childrun = 0;
	exec_free(ms, pipes, FREE_STRUCT | FREE_CMD | FREE_FDS
		| FREE_PIDS | FREE_REDIR, 1);
}

static int	ex_builtin(t_mini *ms, int n)
{
	if (ft_strcmp("echo", ms->cmd[n].cmd[0]) == 0)
		return (print_echo(ms, ms->cmd[n].cmd, n));
	else if (ft_strcmp("export", ms->cmd[n].cmd[0]) == 0)
		return (exec_export(ms, ms->cmd[n].cmd));
	else if (ft_strcmp("unset", ms->cmd[n].cmd[0]) == 0)
		return (exec_unset(ms));
	else if (ft_strcmp("pwd", ms->cmd[n].cmd[0]) == 0)
		return (exec_pwd());
	else if (ft_strcmp("cd", ms->cmd[n].cmd[0]) == 0)
		return (exec_cd(ms));
	else if (ft_strcmp("env", ms->cmd[n].cmd[0]) == 0)
		return (exec_env(ms));
	else if (ft_strcmp("exit", ms->cmd[n].cmd[0]) == 0)
		return (exec_exit(ms, n), 0);
	return (1);
}

static void	run_child(t_mini *ms, int pipes, int n, int i)
{
	ms->pid[i] = fork();
	if (ms->pid[i] < 0)
	{
		perror("Error: ");
		exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
				| FREE_FDS | FREE_PIPES | FREE_PIDS | FREE_REDIR, 1));
	}
	if (ms->pid[i] == 0)
	{
		child_proc(ms, n, pipes);
	}
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
