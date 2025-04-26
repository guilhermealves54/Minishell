/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:00:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/26 13:44:14 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_others(char c, t_mini *ms, int *i);
char	*extract_slash(char *s);
int	check_hdoc(char *s, int *i);

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

int	check_hdoc(char *s, int *i)
{
	int	j;

	j = *i;
	j += 2;
	while (s[j] == ' ' || (s[j] >= 9 && s[j] <= 13))
		j++;
	if (s[j] == '$')
	{
		*i = j;
		return (1);		
	}
	return (0);	
}
