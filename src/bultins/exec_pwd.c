/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:17:46 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/25 16:15:37 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pwd(t_mini *ms, int n)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
		s = ft_strdup(ft_getenv("PWD", ms));
	ft_printf_fd(ms->cmd[n].output_fd, "%s\n", s);
	free(s);
	return (0);
}
