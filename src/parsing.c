/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:07:46 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/07 16:12:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_last_char(t_mini *mini);
static int	errors_redir(t_mini *mini);
static int	char_redir(char c);
static int	redir_err2(char c, char a, int i, t_mini *mini);

// returns 1 if parsing OK
int	parsing(t_mini *mini)
{
	char	c;

	c = get_last_char(mini);
	if (errors_redir(mini))
		return (0);
	if (mini->av[0][0] == '|' || c == '|')
	{
		ft_printf_fd("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

// returns the last char of split for spaces
static char	get_last_char(t_mini *mini)
{
	char	**av;
	int		i;
	int		j;
	char	c;

	i = 0;
	av = mini->av;
	while (av[i])
		i++;
	j = ft_strlen(av[--i]);
	c = av[i][--j];
	return (c);
}

// return 1 if errors 0 otherwise
static int	errors_redir(t_mini *mini)
{
	int		i;
	int		j;
	char	*s;
	char	c;

	s = mini->input;
	i = 0;
	while (s[i])
	{
		if (char_redir(s[i]))
		{
			j = i;
			c = s[i];
			while (s[i] == c)
				i++;
			if (redir_err2(c, s[i], i - j, mini))
				return (1);
		}
		i++;
	}
	return (0);
}

// checks if is a redirection char
static int	char_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

// return 1 if errors 0 otherwise
static int	redir_err2(char c, char a, int i, t_mini *mini)
{
	char	d;

	d = get_last_char(mini);
	if (i > 2)
	{
		ft_printf_fd("minishell: syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	if (char_redir(a))
	{
		ft_printf_fd("minishell: syntax error near unexpected token `%c'\n", a);
		return (1);
	}
	if (!a || char_redir(d))
	{
		ft_printf_fd(
			"minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
