/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:01:58 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/12 17:18:49 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_new_cwd(char *buffer);

void	update_var(char *oldpwd, char *pwd, t_mini *mini)
{
	t_env	*ev;
	char	*temp;

	ev = mini->export;
	while (ev)
	{
		if (ft_strcmp(ev->var, "OLDPWD") == 0)
		{
			temp = ev->content;
			ev->content = oldpwd;
			free(temp);
		}
		else if (ft_strcmp(ev->var, "PWD") == 0)
		{
			temp = ev->content;
			ev->content = pwd;
			free(temp);
		}
		ev = ev->next;
	}
}

char	*get_new_cwd(char *buffer)
{
	int		i;
	char	*new;

	new = ft_strdup(buffer);
	i = ft_strlen(new) - 1;
	while (i >= 0)
	{
		if (new[i] == '/')
		{
			if (i == 0)
				new[++i] = '\0';
			else
				new[i] = '\0';
			break ;
		}
		i--;
	}
	return (new);
}
