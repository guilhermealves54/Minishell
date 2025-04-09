/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:49:52 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/08 18:46:45 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap_var(t_env *current, t_env *next);

void	order_envp(t_mini *mini)
{
	t_env	*head;
	t_env	*current;

	head = mini->export;
	current = head;
	while (current && current->next)
	{
		if (ft_strcmp(current->var, current->next->var) > 0)
		{
			if (current == head)
				head = current->next;
			swap_var(current, current->next);
			current = head;
		}
		else
			current = current->next;
	}
	mini->export = head;
}

static void	swap_var(t_env *current, t_env *next)
{
	if (current->prev)
	{
		current->prev->next = next;
		next->prev = current->prev;
	}
	else
		next->prev = NULL;
	if (next->next)
	{
		next->next->prev = current;
		current->next = next->next;
	}
	else
		current->next = NULL;
	next->next = current;
	current->prev = next;
}
