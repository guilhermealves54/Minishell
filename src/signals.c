/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:50 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/16 15:25:36 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sign_sigint(int sig);

void	setup_signals(void)
{
	signal(SIGINT, sign_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	sign_sigint(int sig)
{
	(void)sig;
	if (g_childrun)
	{
		printf("\n");
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
