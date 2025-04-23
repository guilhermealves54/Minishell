/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:17:46 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/23 17:54:26 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pwd(t_mini *ms, int n)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		perror("Pwd error");
		return (127);
	}
	ft_printf_fd(ms->cmd[n].output_fd, "%s\n", s);
	free(s);
	return (0);
}
