/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:39:58 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/13 19:43:16 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_full_path(char *s);
static char	*get_path(char *s, t_mini *ms);

int	cd_5(t_mini *ms, char **av)
{
	char	*pwd;
	char	*oldpwd;
	char	*s;

	s = get_new_str(av[1]);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(ft_getenv("PWD", ms));
	pwd = get_full_path(s);
	if (pwd)
		update_var(oldpwd, get_path(pwd, ms), ms);
	else
	{
		pwd = ft_strjoin_3(oldpwd, s, '/');
		if (chdir(pwd) == -1)
		{
			printf("minishell: cd: %s: %s\n", s, strerror(errno));
			free_2strings(oldpwd, pwd);
			free(s);
			return (1);
		}
		update_var(oldpwd, pwd, ms);
	}
	free(s);
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
