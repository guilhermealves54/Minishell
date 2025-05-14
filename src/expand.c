/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/14 15:55:25 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_hdoc(char *s, int *i);
void		expand_quotes(char **s, int *a, t_mini *ms);
static char	*expand_dollar(char *s, int i, t_mini *ms, int *b);
static char	*ft_join_3(char *first, char *content, char *last);

char	*expand(char *s, t_mini *ms, int option)
{
	int		i;

	i = 0;
	s = extract_slash(s);
	while (s[i])
	{
		if (ft_strncmp(s + i, "<<", 2) == 0 && check_hdoc(s, &i))
			;
		else if (option && s[i] == '\'' && check_closed_quotes(s + i, 0))
			update_i(s, &i, s[i]);
		else if (s[i] == '\\' && s[i + 1] == '\"')
			i++;
		else if (s[i] == '\"' && check_closed_quotes(s + i, 0))
			expand_2(&s, &i, ms);
		else if (s[i] == '$' && expand_ok(s[i +1]))
		{
			expand_quotes(&s, &i, ms);
			ms->ep++;
		}
		else if (s[i] == '~')
			expand_quotes(&s, &i, ms);
		i++;
	}
	return (s);
}

static int	check_hdoc(char *s, int *i)
{
	int	j;

	j = *i;
	j += 2;
	while (s[j] == ' ' || (s[j] >= 9 && s[j] <= 13))
		j++;
	if (s[j] == '$')
	{
		*i = j;
		return (1);
	}
	return (0);
}

void	expand_quotes(char **s, int *a, t_mini *ms)
{
	char	*temp;
	int		b;

	b = 0;
	temp = *s;
	*s = expand_dollar(*s, *a, ms, &b);
	free(temp);
	*a = ft_strlen(*s) - b - 1;
}

static char	*expand_dollar(char *s, int i, t_mini *ms, int *b)
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
	return (*b = ft_strlen(s + i), ms->expand.last);
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
