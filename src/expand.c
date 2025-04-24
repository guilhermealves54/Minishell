/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/24 15:46:22 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_quotes(char **s, int *a, t_mini *ms);
static char	*expand_dollar(char *s, int i, t_mini *ms);
static char	*ft_join_3(char *first, char *content, char *last);
static void	expand_2(char **s, int *i, t_mini *ms);

char	*expand(char *s, t_mini *ms)
{
	int		i;
	char	*str;

	i = 0;
	s = extract_slash(s);
	str = check_expand(s);
	while (s[i])
	{
		if (ft_strncmp(s + i, "<<$", 3) == 0)
			i += 2;
		else if (ft_strncmp(s + i, "<< $", 4) == 0)
			i += 3;
		else if (s[i] == '\'')
			update_i(s, &i, s[i]);
		else if (s[i] == '\\' && s[i + 1] == '\"')
			i++;
		else if (s[i] == '\"')
			expand_2(&s, &i, ms);
		else if (s[i] == '$' && expand_ok(s[i +1]))
			expand_quotes(&s, &i, ms);
		else if (s[i] == '~')
			expand_quotes(&s, &i, ms);
		i++;
	}
	free(str);
	return (s);
}

static void	expand_2(char **s, int *i, t_mini *ms)
{
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != '\"')
	{
		if ((*s)[*i] == '\\' && (*s)[*i + 1] == '\"')
		{
			(*i)++;
		}
		else if ((*s)[*i] == '$' && expand_ok((*s)[*i + 1]))
		{
			expand_quotes(s, i, ms);
			break ;
		}
		(*i)++;
	}
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
	if (s[i] == '~')
	{
		ms->expand.content = ft_strdup(get_home(ms, "HOME"));
		i++;
	}
	else if (ft_isdigit(s[++i]))
	{
		if (s[i++] == '0')
			ms->expand.content = ft_strdup("minishell");
	}
	else if (!ft_isalpha(s[i]))
		expand_others(s[i], ms, &i);
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
