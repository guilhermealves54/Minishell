/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/09 18:25:17 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cnt_strings(char **av);
static void	crt_pipes(int pipes, int ***fds);
static void	init_cmd(t_mini *ms, int childs, int **fds);
static int	check_cmd(char *cmd);

int	execute_cmd(t_mini *ms)
{
	int		proc;
	int		pipes;
	int		**fds;

	proc = cnt_strings(ms->ap);
	pipes = proc - 1;
	fds = NULL;
	ms->cmd = malloc(proc * sizeof(t_cmd));
	if (!ms->cmd)
	{
		ft_printf_fd("Error allocating memory\n");
		//FREE MEMORY
		exit(1);
	}
	if (pipes > 0)
		crt_pipes(pipes, &fds);
	init_cmd(ms, proc, fds);
	//CREATE FUNCTION TO CLOSE ALL FDS

	//COUNT HOW MANY PROCESSES ARE NOT BUILTINS
	int		n;
	int		pid_n;
	int		*pid;

	n = 0;
	pid_n = 0;
	pid = NULL;
	while (n <= proc)
	{
		if (ms->cmd[n].builtin == 0)
			pid_n++;
		n++;
	}

	//CREATE PID ARRAY
	if (pid_n > 0)
	{
		pid = malloc(pid_n * sizeof(int));
		if (!pid)
		{
			ft_printf_fd("Error allocating memory for PIDs\n");
			//FREE MEMORY
			exit(1);
		}
	}
	//FORK PROCESSES OR EXECUTE BUILTINS
	fork_proc(ms, pid, proc);
	return (0);
}

static void	crt_pipes(int pipes, int ***fds)
{
	int	n;

	fds = malloc(pipes * sizeof(int *));
	if (!fds)
	{
		ft_printf_fd("Error allocating memory\n");
		//FREE MEMORY
		exit(1);
	}
	n = 0;
	while (n < pipes)
	{
		fds[n] = malloc(2 * sizeof(int));
		if (!fds[n])
		{
			ft_printf_fd("Error allocating memory\n");
			///FREE MEMORY
			exit(1);
		}
		if (pipe(fds[n]) == -1)
		{
			ft_printf_fd("Error creating pipes\n");
			//FREE MEMORY
			exit(1);
		}
		n++;
	}
}

static void	init_cmd(t_mini *ms, int proc, int **fds)
{
	int		n;

	n = 0;
	while (n < proc)
	{
		ms->cmd[n].index = n;
		ms->cmd[n].cmd = ft_split_quotes(ms->ap[n], ' ');
		ms->cmd[n].path = ms->cmd[n].cmd[0];
		if (n == 0)
			ms->cmd[n].input_fd = STDIN_FILENO;
		else
			ms->cmd[n].input_fd = fds[n - 1][0];
		if (n == proc - 1)
			ms->cmd[n].output_fd = STDOUT_FILENO;
		else
			ms->cmd[n].output_fd = fds[n][1];
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
