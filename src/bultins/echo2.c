/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:34:59 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/21 14:53:42 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_str(char *str, char *s, int *i, int *j);

// extract quotes from string
char	*get_new_str(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strdup(s);
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\"')
		{
			str[j++] = s[i++];
			str[j++] = s[i++];
		}
		else if (char_quotes(s[i]))
			new_str(str, s, &i, &j);
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

static void	new_str(char *str, char *s, int *i, int *j)
{
	char	c;

	c = s[(*i)++];
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == '\\' && s[*i + 1] == '\"')
		{
			str[(*j)++] = s[(*i)++];
			str[(*j)++] = s[(*i)++];
		}
		else
		{
			str[(*j)++] = s[(*i)++];
		}
	}
	if (s[*i] == c)
		(*i)++;
}
