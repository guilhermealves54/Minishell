/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:01:58 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/25 19:49:59 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*get_new_cwd(char *buffer);
char		*get_home(t_mini *ms, char *home);
static void	check_pwd(t_mini *ms, char *pwd, char *oldpwd);

void	update_var(char *oldpwd, char *pwd, t_mini *mini)
{
	t_env	*ev;
	char	*temp;

	ev = mini->export;
	check_pwd(mini, pwd, oldpwd);
	while (ev)
	{
		if (ft_strcmp(ev->var, "OLDPWD") == 0)
		{
			temp = ev->content;
			ev->content = oldpwd;
			if (temp)
				free(temp);
		}
		else if (ft_strcmp(ev->var, "PWD") == 0)
		{
			temp = ev->content;
			ev->content = pwd;
			if (temp)
				free(temp);
		}
		ev = ev->next;
	}
}

static void	check_pwd(t_mini *ms, char *pwd, char *oldpwd)
{
	if (!ft_getenv("OLDPWD", ms))
		free(oldpwd);
	if (!ft_getenv("PWD", ms))
		free(pwd);
}

char	*get_new_cwd(char *buffer)
{
	int		i;
	char	*new;

	if (!buffer)
		return (NULL);
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

char	*get_home(t_mini *ms, char *home)
{
	char	*new;

	new = ft_getenv(home, ms);
	if (new)
		return (new);
	else
		return (getenv(home));
}
