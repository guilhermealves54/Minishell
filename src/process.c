/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:24 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/10 01:24:32 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ex_builtin(t_mini *ms, int n);
static int	signal_sts(int sts);
static char	*get_path(t_mini *ms);
static void	child_proc(t_mini *ms, int n, int pipes);

void	fork_proc(t_mini *ms, int *pid, int proc, int pipes)
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
			g_childrun = 1;
			pid[i] = fork();
			if (pid < 0)
			{
				perror("Could not fork process");
				split_memfree(&ms);
				free(ms->input);
				//free struct OPT - FREE CMD
				clean_list(ms);
				//free pid array
				if (pipes > 0)
				{
					//close all pipes
				}
				exit(1);
			}
			if (pid[i] == 0)
				child_proc(ms, n, pipes);
			waitpid(pid[i], &ms->cmd[n].sts, 0);
			g_childrun = 0;
			if (WIFSIGNALED(ms->cmd[n].sts))
				ms->exit_status = (signal_sts(ms->cmd[n].sts));
			ms->exit_status = WEXITSTATUS(ms->cmd[n].sts);
			i++;
		}
		n++;
	}
	//free struct OPT - FREE CMD
	//free path
	//if pipes > 0 - close pipes
	//if pid - free pid array
}

static int	ex_builtin(t_mini *ms, int n)
{
	if (ft_strcmp("echo", ms->cmd[n].cmd[0]) == 0)
		return (print_echo(ms->cmd[n].cmd), 0);//remove force ret
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

static char	*get_path(t_mini *ms)
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
		temp = ft_strjoin_3(path[i], ms->av[0], '/');
		if (access(temp, X_OK) == 0)
			return (free_mem(path), temp);
		free(temp);
		i++;
	}
	return (free_mem(path), NULL);
}

static void	child_proc(t_mini *ms, int n, int pipes)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (access (ms->cmd[n].path, X_OK) != 0)
		ms->cmd[n].path = get_path(ms);
	if (!ms->cmd[n].path)
	{
		ft_printf_fd ("Command not found: %s\n", ms->av[0]);
		clean_list(ms);
		split_memfree(&ms);
		free(ms->input);
		//free struct OPT - FREE CMD
		//free pid array
		if (pipes > 0)
		{
			//close pipes
		}
		exit (127);
	}
	dup2(STDIN_FILENO, ms->cmd[n].input_fd);
	dup2(STDOUT_FILENO, ms->cmd[n].output_fd);
	execve (ms->cmd[n].path, ms->av, ms->envp);
	split_memfree(ms);
	free(ms->input);
	//free path
	//free struct OPT - FREE CMD
	//free pid array
	clean_list(ms);
	if (pipes > 0)
	{
		//close pipes
	}
	exit (1);
}
