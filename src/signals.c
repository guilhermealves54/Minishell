/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:50 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/24 02:28:50 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig);
void	chk_signal(t_mini *ms);
void	heredoc_setsignals(void);
void	heredoc_sigint(int sig);

void	ms_signals(void)
{
	g_signal = 0;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler(int sig)
{
	g_signal = sig;
}

void	chk_signal(t_mini *ms)
{
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ms->exit_status = 130;
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
	{
		ms->exit_status = 131;
		g_signal = 0;
	}
}

void	heredoc_setsignals(void)
{
	g_signal = 0;
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
