/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/07 19:06:12 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd(t_mini *ms);
static int	*crt_pipes(int pipes, t_mini *ms);
static int	cnt_strings(char **av);

int	execute_cmd(t_mini *ms)
{
	int		i;
	int		*pipes;
	int		childs;
//	char	**av;

	i = 0;
	childs = cnt_strings(ms->ap);
	pipes = crt_pipes(childs -1, ms);
	/* while (ms->ap[i])
	{
		av = ft_split_quotes(ms->ap[i], ' ');
		if (!av)
			return (1);		
	} */
	return (0);	
}

static int	*crt_pipes(int pipes, t_mini *ms)
{
	if (pipes == 0)
	{
		check_cmd(ms);
		return (NULL);
	}
	return (NULL);
}

static int	check_cmd(t_mini *ms)
{
	if (ft_strcmp("echo", ms->av[0]) == 0)
		return (print_echo(ms->av), 0);
	else if (ft_strcmp("export", ms->av[0]) == 0)
		return(0);
	else if (ft_strcmp("unset", ms->av[0]) == 0)
		return(0);
	else if (ft_strcmp("pwd", ms->av[0]) == 0)
		return(0);
	else if (ft_strcmp("cd", ms->av[0]) == 0)
		return(0);
	else if (ft_strcmp("env", ms->av[0]) == 0)
		return(0);
	else if (ft_strcmp("exit", ms->av[0]) == 0)
		return(0);
	else
		return(0);	//RUN CHILD & EXECVE
}

static int	cnt_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
