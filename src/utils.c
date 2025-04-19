/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:54:13 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/19 14:49:20 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		char_quotes(char c);
char	*ft_strjoin_3(char *path, char *cmd, char c);
int		pidnbr_cnt(t_mini *ms, int proc);
int		cnt_strings(char **av);

int	check_closed_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] == '\"')
			i++;
		else if (input[i] == '\'' || input[i] == '\"')
		{
			update_i(input, &i, input[i]);
			if (!input[i])
			{
				printf("Not closed quotes\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	char_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_strjoin_3(char *path, char *cmd, char c)
{
	char	*s;
	int		i;
	int		len;

	if (!path || !cmd)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (path[i])
	{
		s[i] = path[i];
		i++;
	}
	s[i++] = c;
	while (*cmd)
	{
		s[i] = *cmd++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	pidnbr_cnt(t_mini *ms, int proc)
{
	int		n;
	int		pid_n;

	n = 0;
	pid_n = 0;
	while (n < proc)
	{
		if (ms->cmd[n].builtin == 0)
			pid_n++;
		n++;
	}
	return (pid_n);
}

int	cnt_strings(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
