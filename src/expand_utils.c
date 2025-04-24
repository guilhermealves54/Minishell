/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:00:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/24 15:45:01 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_others(char c, t_mini *ms, int *i);
char	*extract_slash(char *s);
char	*check_expand(char *s);

int	expand_ok(char c)
{
	if (ft_isalnum(c) || c == '$' || c == '?')
		return (1);
	return (0);
}

void	expand_others(char c, t_mini *ms, int *i)
{
	if (c == '$')
	{
		ms->expand.content = ft_itoa(ms->ppid);
		(*i)++;
	}
	else if (c == '?')
	{
		ms->expand.content = ft_itoa(ms->exit_status);
		(*i)++;
	}
}

char	*check_expand(char *s)
{
	char	**av;
	int		i;
	char	*temp;

	i = 0;
	av = ft_split_redir(s, ' ');
	while (av && av[i])
	{
		if (av[i] && av[i + 1])
		{
			if (ft_strcmp(av[i], "<<") == 0 && av[i + 1][0] == '$')
			{
				temp = ft_strdup(av[i + 1]);
				free_mem(av);
				return (temp);
			}
		}
		i++;
	}
	if (av)
		free_mem(av);
	return (NULL);
}

// extract one slash if not inside quotes
char	*extract_slash(char *s)
{
	int		i;
	int		j;
	char	*temp;
	char	c;

	i = 0;
	j = 0;
	temp = ft_strdup(s);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			temp[j++] = s[i++];
			while (s[i] && s[i] != c)
				temp[j++] = s[i++];
		}
		if (s[i] == '\\' && s[i + 1] != '\"')
			i++;
		if (s[i])
			temp[j++] = s[i++];
	}
	temp[j] = '\0';
	free(s);
	return (temp);
}

char	*check_expand(char *s)
{
	char	**av;
	int		i;
	char	*temp;

	i = 0;
	av = ft_split_redir(s, ' ');
	while (av && av[i])
	{
		if (av[i] && av[i + 1])
		{
			if (ft_strcmp(av[i], "<<") == 0 && av[i + 1][0] == '$')
			{
				temp = ft_strdup(av[i + 1]);
				free_mem(av);
				return (temp);
			}
		}
		i++;
	}
	if (av)
		free_mem(av);
	return (NULL);
}
