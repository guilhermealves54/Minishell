/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:41:07 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/14 16:47:06 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(t_mini *ms, int pipes, int n)
{
	if (access(ms->cmd[n].path, F_OK) != 0)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			ms->cmd[n].cmd[0]);
		exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
				| FREE_FDS | FREE_PIPES | FREE_PIDS | FREE_REDIR, 127));
	}
	if (access(ms->cmd[n].path, X_OK) != 0)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n",
			ms->cmd[n].cmd[0]);
		exit (exec_free(ms, pipes, FREE_BASE | FREE_STRUCT | FREE_CMD
				| FREE_FDS | FREE_PIPES | FREE_PIDS | FREE_REDIR, 126));
	}
}
