/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:39:58 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/12 17:17:55 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_full_path(char *s);

int	cd_5(t_mini *ms)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return (1);
	}
	pwd = get_full_path(ms->av[1]);
	if (pwd)
		update_var(oldpwd, ft_strdup(pwd), ms);
	else
	{
		pwd = ft_strjoin_3(oldpwd, ms->av[1], '/');
		if (chdir(pwd) == -1)
		{
			printf("minishell: cd: %s: %s\n", ms->av[1], strerror(errno));
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
