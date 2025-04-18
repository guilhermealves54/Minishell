/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:46:42 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/18 14:49:49 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_size(t_mini *ms)
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
