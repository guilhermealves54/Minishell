/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:08 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/16 18:45:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_mini *ms, int n);
static int	list_size(t_mini *ms);
static char	**new_envp(t_mini *ms);
static void	aft_execve(t_mini *ms, char **envp, int n, int pipes);

void	child_proc(t_mini *ms, int n, int pipes)
{
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (access (ms->cmd[n].path, X_OK) != 0)
		ms->cmd[n].path = get_path(ms, n);
	if (!ms->cmd[n].path)
	{
		if (!ms->cmd[n].cmd[0][0])
			ft_printf_fd ("Command '' not found\n");
		else
			ft_printf_fd ("%s: command not found\n", ms->cmd[n].cmd[0]);
		exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD | FREE_FDS
				| FREE_PIPES | FREE_PIDS, 127));
	}
	envp = new_envp(ms);
	dup2(ms->cmd[n].input_fd, STDIN_FILENO);
	dup2(ms->cmd[n].output_fd, STDOUT_FILENO);
	close_pipes(ms, pipes);
	execve (ms->cmd[n].path, ms->cmd[n].cmd, envp);
	aft_execve(ms, envp, n, pipes);
}

static char	*get_path(t_mini *ms, int n)
{
	char	*home;
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	if (!ms->cmd[n].cmd[0][0])
		return (NULL);
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

static int	list_size(t_mini *ms)
{
	int		size;
	t_env	*start;

	size = 0;
	start = ms->export;
	while (ms->export)
	{
		if (ms->export->content)
			size++;
		ms->export = ms->export->next;
	}
	ms->export = start;
	return (size);
}

static char	**new_envp(t_mini *ms)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = malloc((list_size(ms) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = ms->export;
	while (ms->export)
	{
		if (ms->export->content)
		{
			envp[i] = ft_strjoin_3(ms->export->var, ms->export->content, '=');
			i++;
		}
		ms->export = ms->export->next;
	}
	ms->export = tmp;
	envp[i] = NULL;
	return (envp);
}

static void	aft_execve(t_mini *ms, char **envp, int n, int pipes)
{
	if (ms->cmd[n].cmd[0] != ms->cmd[n].path)
		free(ms->cmd->path);
	if (envp)
		free_mem(envp);
	exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD | FREE_FDS
			| FREE_PIPES | FREE_PIDS, 1));
}
