/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:05:22 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/12 18:55:45 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_redir(char c);
static int	count_strings_redir(char *s, char c);
static void	over_redir(char *s, int *i);
static int	get_all(t_split *sp);

// split with quotes and redirections
char	**ft_split_redir(char *s, char c)
{
	t_split	sp;

	if (!s)
		return (NULL);
	sp.s = s;
	sp.c = c;
	sp.i = 0;
	sp.j = 0;
	sp.av = malloc(sizeof(char *) * (count_strings_redir(s, c) + 1));
	if (!sp.av)
		return (NULL);
	while (s[sp.i])
	{
		while (s[sp.i] == c)
			sp.i++;
		if (!s[sp.i])
			break ;
		if (!get_all(&sp))
			return (NULL);
	}
	sp.av[sp.j] = NULL;
	return (sp.av);
}

static int	get_all(t_split *sp)
{
	int	start;

	start = sp->i;
	if (char_redir(sp->s[sp->i]))
	{
		while (char_redir(sp->s[sp->i]))
			sp->i++;
		sp->av[sp->j++] = get_str(sp->s, start, sp->i);
		if (!sp->av[sp->j -1])
			return (free_mem(sp->av), 0);
	}
	else
	{
		while (sp->s[sp->i] && sp->s[sp->i] != sp->c
			&& !char_redir(sp->s[sp->i]))
		{
			if (sp->s[sp->i] == '\'' || sp->s[sp->i] == '\"')
				update_i(sp->s, &sp->i, sp->s[sp->i]);
			sp->i++;
		}
		sp->av[sp->j++] = get_str(sp->s, start, sp->i);
		if (!sp->av[sp->j -1])
			return (free_mem(sp->av), 0);
	}
	return (1);
}

static int	char_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

// count strings - ft_split with quotes
static int	count_strings_redir(char *s, char c)
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
		if (char_redir(s[i]))
			over_redir(s, &i);
		else
		{
			while (s[i] && s[i] != c && !char_redir(s[i]))
			{
				if (s[i] == '\'' || s[i] == '\"')
					update_i(s, &i, s[i]);
				i++;
			}
		}
	}
	return (j);
}

static void	over_redir(char *s, int *i)
{
	while (char_redir(s[*i]))
		(*i)++;
}
