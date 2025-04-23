/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:46:42 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/23 18:53:38 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_redir(char c);

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

int	char_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char	*ft_getenv(char *var, t_mini *ms)
{
	t_env	*temp;

	temp = ms->export;
	if (ft_strcmp(var, "PWD") == 0)
		return (get_home(ms, "PWD"));
	while (temp)
	{
		if (ft_strcmp(var, temp->var) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}
