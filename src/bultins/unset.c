/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:46:06 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/09 18:23:55 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset(char *s, t_mini *ms);
static void	delete_node(t_env *prev, t_env *next);
static void	free_node(t_env *temp);

int	exec_unset(t_mini *ms)
{
	int	i;

	i = 1;
	while (ms->av[i])
	{
		unset(ms->av[i], ms);
		i++;
	}
	return (0);
}

static void	unset(char *s, t_mini *ms)
{
	t_env	*ev;

	ev = ms->export;
	while (ev)
	{
		if (ft_strcmp(s, ev->var) == 0)
		{
			if (ev == ms->export)
				ms->export = ev->next;
			delete_node(ev->prev, ev->next);
			free_node(ev);
			break ;
		}
		ev = ev->next;
	}
}

static void	delete_node(t_env *prev, t_env *next)
{
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev)
		next->prev = NULL;
	else if (!next)
		prev->next = NULL;
}

static void	free_node(t_env *temp)
{
	if (temp->var)
	{
		free(temp->var);
		temp->var = NULL;
	}
	if (temp->content)
	{
		free(temp->content);
		temp->content = NULL;
	}
	free(temp);
}
