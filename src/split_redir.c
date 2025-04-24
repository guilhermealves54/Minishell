/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:05:22 by ruida-si          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/24 15:28:31 by ruida-si         ###   ########.fr       */
=======
/*   Updated: 2025/04/23 16:29:25 by ruida-si         ###   ########.fr       */
>>>>>>> ac80bb4d872128273b408868df652832ac9b97ca
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strings_redir(char *s, char c, int j, int i);
static void	over_redir(char *s, int *i);
static int	get_all(t_split *sp);
static int	get_all_loop(int start, t_split *sp);

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
	sp.av = malloc(sizeof(char *) * (count_strings_redir(s, c, 0, 0) + 1));
	if (!sp.av)
		return (NULL);
	while (s[sp.i])
	{
<<<<<<< HEAD
		while (s[sp.i] == c || (s[sp.i] >= 9 && s[sp.i] <= 13))
=======
		while (s[sp.i] == c || s[sp.i] < 14)
>>>>>>> ac80bb4d872128273b408868df652832ac9b97ca
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
		if (!get_all_loop(start, sp))
			return (0);
	}
	return (1);
}

static int	get_all_loop(int start, t_split *sp)
{
	while (sp->s[sp->i] && sp->s[sp->i] != sp->c
		&& !char_redir(sp->s[sp->i]))
	{
		if (sp->s[sp->i] == '\\' && sp->s[sp->i + 1] == '\"')
			sp->i++;
		else if (sp->s[sp->i] == '\'' || sp->s[sp->i] == '\"')
			update_i(sp->s, &sp->i, sp->s[sp->i]);
		sp->i++;
	}
	sp->av[sp->j++] = get_str(sp->s, start, sp->i);
	if (!sp->av[sp->j -1])
		return (free_mem(sp->av), 0);
	return (1);
}

// count strings - ft_split with quotes
static int	count_strings_redir(char *s, char c, int j, int i)
{
	while (s[i])
	{
<<<<<<< HEAD
		while (s[i] == c || (s[i] >= 9 && s[i] <= 13))
=======
		while (s[i] == c || s[i] < 14)
>>>>>>> ac80bb4d872128273b408868df652832ac9b97ca
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
				if (s[i] == '\\' && s[i + 1] == '\"')
					i++;
				else if (s[i] == '\'' || s[i] == '\"')
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
