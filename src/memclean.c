/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:43 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:20:44 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_list(t_mini *ms)
{
	t_env	*tmp;

	while (ms->export)
	{
		tmp = ms->export->next;
		free(ms->export->var);
		free(ms->export);
		ms->export = tmp;
	}
}
