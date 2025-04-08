/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/08 15:42:45 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_quotes(char **s, int *a, t_mini *ms);
static char	*expand_dollar(char *s, int i, t_mini *ms);
static char	*ft_join_3(char *first, char *content, char *last);
char		*ft_getenv(char *var, t_mini *ms);

char	*expand(char *s, t_mini *ms)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			update_i(s, &i, s[i]);
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				if (s[i] == '$')
				{
					expand_quotes(&s, &i, ms);
					break ;
				}
				i++;
			}
		}
		else if (s[i] == '$')
			expand_quotes(&s, &i, ms);
		i++;
	}
	return (s);
}

static void	expand_quotes(char **s, int *a, t_mini *ms)
{
	char	*temp;

	temp = *s;
	*s = expand_dollar(*s, *a, ms);
	free(temp);
	*a = -1;
}

static char	*expand_dollar(char *s, int i, t_mini *ms)
{
	ms->expand.content = NULL;
	ms->expand.first = get_str(s, 0, i);
	if (ft_isdigit(s[++i]))
	{
		if (s[i++] == '0')
			ms->expand.content = ft_strdup("minishell");
	}
	else if (s[i] == '$')
		ms->expand.content = ft_itoa(ms->ppid);
	else if (s[i] == '?')
	{
		ms->expand.content = ft_itoa(ms->exit_status);
		i++;
	}
	else
	{
		ms->expand.start = i;
		while (ft_isalnum(s[i]))
			i++;
		ms->expand.var = get_str(s, ms->expand.start, i);
		ms->expand.content = ft_strdup(ft_getenv(ms->expand.var, ms));
		free(ms->expand.var);
	}
	ms->expand.last = ft_join_3(ms->expand.first, ms->expand.content, s + i);
	return (ms->expand.last);
}

static char	*ft_join_3(char *first, char *content, char *last)
{
	char	*final;
	char	*temp;

	if (content)
	{
		temp = ft_strjoin(first, content);
		free_2strings(first, content);
		final = ft_strjoin(temp, last);
		if (temp)
			free(temp);
	}
	else
	{
		final = ft_strjoin(first, last);
		free(first);
	}
	return (final);
}

char	*ft_getenv(char *var, t_mini *ms)
{
	t_env	*temp;

	temp = ms->export;
	while (temp)
	{
		if (ft_strcmp(var, temp->var) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}
