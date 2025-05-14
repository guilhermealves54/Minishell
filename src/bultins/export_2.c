/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:13:54 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/14 20:16:22 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_slash(char *s, int j);
static void	count_spec_char(const char *content, int *i, int *j);
static void	add_slash_2(const char *s, char *str, int *i, int *j);

char	*check_content(char *content)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '\\' && content[i + 1] == '$')
			i++;
		else if (char_quotes(content[i]))
			count_spec_char(content, &i, &j);
		else if (content[i] == '$')
			j++;
		i++;
	}
	if (j > 0)
		content = add_slash(content, j);
	return (content);
}

static void	count_spec_char(const char *content, int *i, int *j)
{
	char	c;

	c = content[(*i)++];
	while (content[*i] && content[*i] != c)
	{
		if (content[*i] == '\\' && content[*i + 1] == '$')
			*i += 1;
		else if (content[*i] == '\\' || content[*i] == '\"'
			|| content[*i] == '$')
			(*j)++;
		(*i)++;
	}
}

static char	*add_slash(char *s, int j)
{
	int		i;
	char	*str;

	i = ft_strlen(s) + j + 1;
	str = malloc(i);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (char_quotes(s[i]))
			add_slash_2(s, str, &i, &j);
		if (s[i] == '\\' && s[i + 1] == '$')
		{
			str[j++] = s[i++];
			str[j++] = s[i++];
		}
		if (s[i] == '$')
			str[j++] = '\\';
		if (s[i])
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (free(s), str);
}

static void	add_slash_2(const char *s, char *str, int *i, int *j)
{
	char	c;

	c = s[*i];
	str[*j] = s[*i];
	(*j)++;
	(*i)++;
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == '\\' || s[*i] == '\"' || s[*i] == '$')
		{
			str[*j] = '\\';
			(*j)++;
		}
		str[*j] = s[*i];
		(*j)++;
		(*i)++;
	}
	if (s[*i])
	{
		str[*j] = s[*i];
		(*j)++;
		(*i)++;
	}
}
