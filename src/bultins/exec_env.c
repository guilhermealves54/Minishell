/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:29:52 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/23 17:59:42 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_mini *ms, int n)
{
	t_env	*ev;
	char	**av;

	av = ms->cmd[n].cmd;
	if (av[1])
	{
		ft_printf_fd(2, "No options allowed\n");
		return (127);
	}
	ev = ms->export;
	while (ev)
	{
		if (ev->content)
			ft_printf_fd(ms->cmd[n].output_fd, "%s=%s\n", ev->var, ev->content);
		ev = ev->next;
	}
	return (0);
}
