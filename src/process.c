/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:42:24 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/08 17:46:40 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_mini *ms);
static void	child_proc(t_mini *ms);

int	fork_proc(t_mini *ms)
{
	int	pid;
	int	sts;
	int	sig;

	pid = fork();
	if (pid < 0)
	{
		perror("Could not fork process");
		exit(1);
	}
	sts = 0;
	g_childrun = 1;
	if (pid == 0)
		child_proc(ms);
	waitpid(pid, &sts, 0);
	if (WIFSIGNALED(sts))
	{
		sig = WTERMSIG(sts);
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
	}
	g_childrun = 0;
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

static void	child_proc(t_mini *ms)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (access (ms->av[0], X_OK) == 0)
		path = ms->av[0];
	else
		path = get_path(ms);
	if (!path)
	{
		ft_printf_fd ("Command not found: %s\n", ms->av[0]);
		clean_list(ms);
		split_memfree(ms);
		free(ms->input);
		exit (127);
	}
	execve (path, ms->av, ms->envp);
	clean_list(ms);
	split_memfree(ms);
	free(ms->input);
	exit (1);
}
