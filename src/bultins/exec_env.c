/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:29:52 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/09 18:21:03 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_mini *ms)
{
	t_env	*ev;

	if (ms->av[1])
	{
		ft_printf_fd("No options allowed\n");
		return (127);
	}
	ev = ms->export;
	while (ev)
	{
		if (ev->content)
			printf("%s=%s\n", ev->var, ev->content);
		ev = ev->next;
	}
	return (0);
}
