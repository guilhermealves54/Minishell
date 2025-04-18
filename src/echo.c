/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:55:02 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/16 18:41:19 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	multiple_nl(char **av, int *a);
static void	print_quotes(t_mini *ms, int n, char *s);
static int	check_new_line(char *s, int	*a);
char		*get_new_str(char *s);

int	print_echo(t_mini *ms, char **av, int n)
{
	int	i;
	int	a;

	i = 1;
	a = multiple_nl(av, &i);
	while (av[i])
	{
		print_quotes(ms, n, av[i]);
		i++;
		if (av[i])
			write(ms->cmd[n].output_fd, " ", 1);
	}
	if (a)
		write(ms->cmd[n].output_fd, "\n", 1);
	return (0);
}

static int	multiple_nl(char **av, int *a)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_new_line(av[i], a))
			break ;
		i++;
	}
	if (i == 1)
		return (1);
	else
		return (0);
}

static void	print_quotes(t_mini *ms, int n, char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (char_quotes(s[i]))
		{
			c = s[i++];
			while (s[i] != c)
			{
				write(ms->cmd[n].output_fd, &s[i], 1);
				i++;
			}
		}
		else
			write(ms->cmd[n].output_fd, &s[i], 1);
		i++;
	}
}

static int	check_new_line(char *s, int	*a)
{
	int	i;

	s = get_new_str(s);
	if (s)
	{
		i = 1;
		if (ft_strncmp(s, "-n", 2) == 0)
		{
			while (s[i] == 'n')
				i++;
			if (s[i])
			{
				free(s);
				return (1);
			}
			else
			{
				(*a)++;
				free(s);
				return (0);
			}
		}
		free(s);
	}
	return (1);
}

// extract quotes from string
char	*get_new_str(char *s)
{
	char	*str;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	str = ft_strdup(s);
	while (s[i])
	{
		if (char_quotes(s[i]))
		{
			c = s[i++];
			while (s[i] && s[i] != c)
			{
				str[j++] = s[i++];
			}
			i++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
