/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:46:42 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/15 00:21:33 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		char_redir(char c);
char	*ft_getenv(char *var, t_mini *ms);
char	*check_quotes(char *file, int *quotes);

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
	while (temp)
	{
		if (ft_strcmp(var, temp->var) == 0)
			return (temp->content_qts);
		temp = temp->next;
	}
	return (NULL);
}

char	*check_quotes(char *file, int *quotes)
{
	char	*s;

	if (file[0] == '\"' || file[0] == '\'')
	{
		*quotes = 1;
		s = get_new_str(file);
		return (s);
	}
	*quotes = 0;
	return (ft_strdup(file));
}
