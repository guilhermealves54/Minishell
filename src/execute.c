/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/09 02:27:57 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd(t_mini *ms);
static int	*crt_pipes(int pipes, t_mini *ms);
static int	cnt_strings(char **av);

int	execute_cmd(t_mini *ms)
{
	int		i;
	int		childs;
	int		pipes;
	int		**fds;

	childs = cnt_strings(ms->ap);
	pipes = childs - 1;
	printf("Number of processes: %i\n", childs);

	//ALLOCATE MEMORY TO ARRAY OF STRUCTS
	ms->cmd = malloc(childs * sizeof(t_cmd));
	if (!ms->cmd)
	{
		ft_printf_fd("Error allocating memory\n");
		//FREE MEMORY
		exit(1);
	}

	//ALLOCATE MEMORY TO FDS AND CREATE PIPES
	int	n;

	if (pipes > 0)
	{
		fds = malloc(pipes * sizeof(int *));
		if (!fds)
			ft_printf_fd("Error allocating memory\n");
			//FREE MEMORY
			exit(1);
		while (n <= pipes)
		{
			fds[n] = malloc(2 * sizeof(int));
			if (!fds[n])
			ft_printf_fd("Error allocating memory\n");
			///FREE MEMORY
			exit(1);
			n++;
			if (pipe(fds[n]) == -1)
			{
				ft_printf_fd("Error creating pipes\n");
				//FREE MEMORY
				exit(1);
			}
		}
	}

	//LOOP TO INIT CMD STRUCT
	int		n;

	n = 0;
	while (n < childs)
	{
		ms->cmd[n]->index = n;
		ms->cmd[n]->cmd = ft_split_quotes(ms->ap[n], ' ');
		ms->cmd[n]->path = ms->cmd[n]->cmd[0];
		if (n == 0)
			ms->cmd[n]->input_fd = STDIN_FILENO;
		else
			ms->cmd[n]->input_fd = fds[n - 1][0];
		if (n == childs - 1)
			ms->cmd[n]->output_fd = STDOUT_FILENO;
		else
			ms->cmd[n]->output_fd = fds[n][1];
		ms->cmd[n]->sts = 0;
		n++;
	}
	//CREATE FUNCTION TO CLOSE ALL FDS

	return (0);
}

// Function to be deleted
static int	*crt_pipes(int pipes, t_mini *ms)
{
	if (pipes == 0)
	{
		check_cmd(ms);
		return (NULL);
	}
	return (NULL);
}

// Update function. Builtins will read from command struct too.
static int	check_cmd(t_mini *ms)
{
	if (ft_strcmp("echo", ms->av[0]) == 0)
		return (print_echo(ms->av), 0);
	else if (ft_strcmp("export", ms->av[0]) == 0)
		return (0);
	else if (ft_strcmp("unset", ms->av[0]) == 0)
		return (0);
	else if (ft_strcmp("pwd", ms->av[0]) == 0)
		return (0);
	else if (ft_strcmp("cd", ms->av[0]) == 0)
		return (0);
	else if (ft_strcmp("env", ms->av[0]) == 0)
		return (0);
	else if (ft_strcmp("exit", ms->av[0]) == 0)
		return (0);
	else
		ms->exit_status = fork_proc(ms);
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
