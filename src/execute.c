/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/11 17:15:06 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cnt_strings(char **av);
static int	**crt_pipes(t_mini *ms, int pipes);
static void	init_cmd(t_mini *ms, int childs, int pipes);
static int	check_cmd(char *cmd);
char		**get_cmd(char	*ap);

//COUNT HOW MANY PROCESSES ARE NOT BUILTINS
int	pidnbr_cnt(t_mini *ms, int proc)
{
	int		n;
	int		pid_n;

	n = 0;
	pid_n = 0;
	while (n < proc)
	{
		if (ms->cmd[n].builtin == 0)
			pid_n++;
		n++;
	}
	return (pid_n);
}

//CREATE PID ARRAY
int	*crt_pid_arr(t_mini *ms, int pid_n, int pipes)
{
	int	*pid;
	
	pid = NULL;
	if (pid_n > 0)
	{
		pid = malloc((pid_n) * sizeof(int));
		if (!pid)
		{
			ft_printf_fd("minishell: error allocating memory\n");	
			exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
				| FREE_FDS | FREE_PIPES, 1));
		}
	}
	return (pid);
}

void	execute_cmd(t_mini *ms)
{
	int		proc;
	int		pipes;

	proc = cnt_strings(ms->ap);
	pipes = proc - 1;
	ms->fds = NULL;
	ms->pid = NULL;
	ms->cmd = malloc(proc * sizeof(t_cmd));
	if (!ms->cmd)
	{
		ft_printf_fd("minishell: error allocating memory\n");	
		exit(exec_free(ms, pipes, FREE_BASE, 1));
	}
	if (pipes > 0)
		ms->fds = crt_pipes(ms, pipes);
	init_cmd(ms, proc, pipes);
	if (pidnbr_cnt(ms, proc) > 0)
		ms->pid = crt_pid_arr(ms, pidnbr_cnt(ms, proc), pipes);
	fork_proc(ms, proc, pipes);
}

static int	**crt_pipes(t_mini *ms, int pipes)
{
	int	n;

	ms->fds = malloc(pipes * sizeof(int *));
	if (!ms->fds)
	{
		ft_printf_fd("minishell: error allocating memory\n");	
		exit(exec_free(ms, pipes, FREE_BASE | FREE_STRUCT, 1));
	}
	n = 0;
	while (n < pipes)
	{
		ms->fds[n] = malloc(2 * sizeof(int));
		if (!ms->fds[n])
		{
			ft_printf_fd("minishell: error allocating memory\n");	
			exit(exec_free(ms, n, FREE_BASE | FREE_STRUCT | FREE_FDS, 1));
		}
		if (pipe(ms->fds[n]) == -1)
		{
			ft_printf_fd("minishell: error allocating memory\n");
			exec_free(ms, n, FREE_PIPES, 1);
			exit(exec_free(ms, n + 1, FREE_BASE | FREE_STRUCT | FREE_FDS, 1));
		}
		n++;
	}
	return (ms->fds);
}

char	**get_cmd(char	*ap)
{
	char	*temp;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_quotes(ap, ' ');
	while (cmd[i])
	{
		temp = cmd[i];
		cmd[i] = get_new_str(cmd[i]);
		free(temp);
		i++;
	}
	return (cmd);
}

static void	init_cmd(t_mini *ms, int proc, int pipes)
{
	int		n;

	n = 0;
	while (n < proc)
	{
		ms->cmd[n].index = n;
		ms->cmd[n].cmd = get_cmd(ms->ap[n]);
		if (!ms->cmd[n].cmd)
		{
			ft_printf_fd("minishell: error allocating memory\n");	
			exit(exec_free(ms, n, FREE_BASE | FREE_STRUCT | FREE_FDS
				| FREE_PIPES, 1));
		}
		ms->cmd[n].path = ms->cmd[n].cmd[0];
		if (pipes > 0)
		{
			if (n == 0)
				ms->cmd[n].input_fd = STDIN_FILENO;
			else
				ms->cmd[n].input_fd = ms->fds[n - 1][0];
			if (n == proc - 1)
				ms->cmd[n].output_fd = STDOUT_FILENO;
			else
				ms->cmd[n].output_fd = ms->fds[n][1];
		}
		else
		{
			ms->cmd[n].input_fd = STDIN_FILENO;
			ms->cmd[n].output_fd = STDOUT_FILENO;
		}
		ms->cmd[n].sts = 0;
		ms->cmd[n].builtin = check_cmd(ms->cmd[n].cmd[0]);
		n++;
	}
}

static int	check_cmd(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
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

static int	cnt_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
