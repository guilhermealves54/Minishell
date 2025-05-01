/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:07:46 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/01 12:57:33 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	errors_redir(t_mini *mini);
static int	redir_err2(char c, char a, int i, t_mini *mini);
static int	check_aft_redir(t_mini *ms);
static void	print_error(char c);

// returns 1 if parsing OK
int	parsing(t_mini *mini)
{
	char	c;

	if (!mini->av || !mini->av[0])
		return (0);
	c = get_last_char(mini);
	if (errors_redir(mini))
		return (0);
	if (mini->av[0][0] == '|' || c == '|')
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

// return 1 if errors 0 otherwise
static int	errors_redir(t_mini *mini)
{
	int		i;
	int		j;
	char	*s;
	char	c;

	if (!check_aft_redir(mini))
		return (1);
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

static int	check_aft_redir(t_mini *ms)
{
	char	**av;
	int		i;

	i = 0;
	av = ms->av;
	while (av[i])
	{
		if (is_redir(av[i]) && !av[i + 1])
		{
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `newline'\n");
			g_exit_status = 2;
			return (0);
		}
		if (is_redir(av[i]) && av[i +1][0] == '|')
		{
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `|'\n");
			g_exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

// return 1 if errors 0 otherwise
static int	redir_err2(char c, char a, int i, t_mini *mini)
{
	char	d;
	int		j;

	j = 0;
	d = get_last_char(mini);
	if (i > 2)
	{
		print_error(c);
		j = 1;
	}
	else if (char_redir(a))
	{
		print_error(a);
		j = 1;
	}
	else if (!a || char_redir(d))
	{
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token `newline'\n");
		j = 1;
	}
	if (j == 1)
		g_exit_status = 2;
	return (j);
}

static void	print_error(char c)
{
	ft_printf_fd(2,
		"minishell: syntax error near unexpected token `%c'\n", c);
}
