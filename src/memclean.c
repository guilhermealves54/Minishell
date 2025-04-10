/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:43 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/07 17:19:16 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char **av);
void	split_memfree(t_mini *ms);
void	free_2strings(char *s1, char *s2);

//	Used to clean the t_env list.
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

//	Possible combine with free_mem() to save space
void	split_memfree(t_mini *ms)
{
	free_mem(ms->av);
	free_mem(ms->ap);
}

void	free_2strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}
