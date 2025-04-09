/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:12:42 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/09 20:02:09 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_1(t_mini *ms);
void	update_var(char *oldpwd, char *pwd, t_mini *mini);

int	exec_cd(t_mini *ms)
{
	if (cnt_strings(ms->av) > 2)
	{
		ft_printf_fd("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!ms->av[1] || ft_strcmp(ms->av[1], "~") == 0)
		return (cd_1(ms));
	return (0);
}

static int	cd_1(t_mini *ms)
{
	char	*oldpwd;
	char	*home;
	
	if (!ms->av[1] && !ft_getenv("HOME", ms))
	{
		ft_printf_fd("minishell: cd: HOME not set\n");
		return (1);		
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return (1);
	}
	home = getenv("HOME");
	if (chdir(home) == -1)
	{
		ft_printf_fd("minishell: cd: %s: %s\n", home, strerror(errno));
		free(oldpwd);
		return (1);
	}
	update_var(oldpwd, ft_strdup(home), ms);
	return (0);
}
