/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:12:42 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/10 16:15:42 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_1(t_mini *ms);
static int	cd_2(t_mini *ms);
static int	cd_3(t_mini *ms);
static int	cd_4(t_mini *ms);

int	exec_cd(t_mini *ms)
{
	if (cnt_strings(ms->av) > 2)
	{
		ft_printf_fd("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (!ms->av[1] || ft_strcmp(ms->av[1], "~") == 0)
		return (cd_1(ms));
	else if (ft_strcmp(ms->av[1], "..") == 0)
		return (cd_2(ms));	
	else if (ft_strcmp(ms->av[1], ".") == 0)
		return (cd_3(ms));
	else if (ft_strcmp(ms->av[1], "-") == 0)
		return (cd_4(ms));
	else
		return (cd_5(ms));
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

static int	cd_2(t_mini *ms)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return (1);
	}
	pwd = get_new_cwd(oldpwd);
	if (chdir(pwd) == -1)
	{
		ft_printf_fd("minishell: cd: %s: %s\n", pwd, strerror(errno));
		free_2strings(oldpwd, pwd);
		return (1);
	}
	update_var(oldpwd, pwd, ms);
	return (0);
}

static int	cd_3(t_mini *ms)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return (1);
	}
	update_var(oldpwd, ft_strdup(oldpwd), ms);
	return (0);	
}

static int	cd_4(t_mini *ms)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return (1);
	}
	pwd = ft_getenv("OLDPWD", ms);
	if (!pwd)
	{
		ft_printf_fd("minishell: cd: OLDPWD not set\n");
		free(oldpwd);
		return (1);
	}
	if (chdir(pwd) == -1)
	{
		ft_printf_fd("minishell: cd: %s: %s\n", pwd, strerror(errno));
		free(oldpwd);
		return (1);
	}
	printf("%s\n", pwd);
	update_var(oldpwd, ft_strdup(pwd), ms);
	return (0);
}
