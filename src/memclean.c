/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:43 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/15 16:51:06 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_list(t_mini *ms);
void	free_mem(char **av);
void	split_memfree(t_mini *ms);
void	free_intarray(t_mini *ms, int pipes);

int	exec_free(t_mini *ms, int pipes, int opt, int ret)
{
	int	i;

	i = 0;
	if (opt & 32)
		if (ms->pid)
			free(ms->pid);
	if (opt & 16)
		free_intarray(ms, pipes);
	if (opt & 8)
		close_pipes(ms, pipes);
	if (opt & 4)
	{
		while ((pipes + 1) > i)
			if (ms->cmd[i].cmd)
				free_mem(ms->cmd[i++].cmd);
	}
	if (opt & 2)
		free(ms->cmd);
	if (opt & 1)
	{
		split_memfree(ms);
		free(ms->input);
		clean_list(ms);
	}
	return (ret);
}

void	clean_list(t_mini *ms)
{
	t_env	*tmp;

	while (ms->export)
	{
		tmp = ms->export->next;
		free(ms->export->var);
		free(ms->export->content);
		free(ms->export);
		ms->export = tmp;
	}
}

void	free_mem(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	split_memfree(t_mini *ms)
{
	free_mem(ms->av);
	free_mem(ms->ap);
}

void	free_intarray(t_mini *ms, int pipes)
{
	if (pipes)
	{
		while (pipes > 0)
		{
			free(ms->fds[pipes - 1]);
			pipes--;
		}
		free(ms->fds);
	}
}
