/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:08:44 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/07 16:38:25 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_slash(char *s, int *i);
static int	count_strings(char *s, char c);
char		*get_str(char *s, int start, int end, int option);
void		update_i(char *s, int *i, char c);

// split with quotes
// option 1 removes quotes 0 not
char	**ft_split_quotes(char *s, char c, int option)
{
	int		i;
	int		j;
	int		start;
	char	**av;

	i = 0;
	j = 0;
	av = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!av)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			skip_slash(s, &i);
		av[j++] = get_str(s, start, i, option);
		if (!av[j - 1])
			return (free_mem(av), NULL);
	}
	av[j] = NULL;
	return (av);
}

static void	skip_slash(char *s, int *i)
{
	if (s[*i] == '\'' || s[*i] == '\"')
		update_i(s, i, s[*i]);
	(*i)++;
}

// count strings - ft_split with quotes
static int	count_strings(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		j++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				update_i(s, &i, s[i]);
			i++;
		}
	}
	return (j);
}

// get string between 2 ends
// 1 removes quotes 0 not
char	*get_str(char *s, int start, int end, int option)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (option && (s[start] == '\'' || s[start] == '\"'))
		{
			start++;
		}
		else
		{
			str[i++] = s[start++];
		}
	}
	str[i] = '\0';
	return (str);
}

void	update_i(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}
