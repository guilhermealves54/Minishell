/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:49:25 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/15 18:41:09 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_mini *ms, int pipes);

void	free_2strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	close_pipes(t_mini *ms, int pipes)
{
	while (pipes > 0)
	{
		close(ms->fds[pipes - 1][0]);
		close(ms->fds[pipes - 1][1]);
		pipes--;
	}
}
