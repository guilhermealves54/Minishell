/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:39:58 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/25 16:04:07 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_full_path(char *s);
static char	*get_path(char *s, t_mini *ms);

int	cd_5(t_mini *ms, char **av)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(ft_getenv("PWD", ms));
	pwd = get_full_path(av[1]);
	if (pwd)
		update_var(oldpwd, get_path(pwd, ms), ms);
	else
	{
		pwd = ft_strjoin_3(oldpwd, av[1], '/');
		if (chdir(pwd) == -1)
		{
			printf("minishell: cd: %s: %s\n", av[1], strerror(errno));
			free_2strings(oldpwd, pwd);
			return (1);
		}
		update_var(oldpwd, pwd, ms);
	}
	return (0);
}

static char	*get_full_path(char *s)
{
	if (chdir(s) == 0)
		return (s);
	return (NULL);
}

static char	*get_path(char *s, t_mini *ms)
{
	if (ft_strchr(s, '/'))
		return (ft_strdup(s));
	else
		s = ft_strjoin_3(ft_getenv("PWD", ms), s, '/');
	return (s);
}
