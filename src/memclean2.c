/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:49:25 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/21 16:50:02 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_mini *ms, int pipes);
void	close_redir(t_mini *ms, int proc);
void	free_base(t_mini *ms);
void	free_cmd(t_mini *ms, int pipes);

void	free_2strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	close_pipes(t_mini *ms, int pipes)
{
	while (pipes > 0)
	{
		close(ms->fds[pipes - 1][0]);
		close(ms->fds[pipes - 1][1]);
		pipes--;
	}
}

void	close_redir(t_mini *ms, int proc)
{
	while (proc >= 0)
	{
		if (ms->cmd[proc].redirin != -1)
			close(ms->cmd[proc].redirin);
		if (ms->cmd[proc].redirout != -1)
			close(ms->cmd[proc].redirout);
		proc--;
	}
}

void	free_base(t_mini *ms)
{
	split_memfree(ms);
	free_2strings(ms->prompt, ms->input);
	clean_list(ms);
}

void	free_cmd(t_mini *ms, int pipes)
{
	int	i;

	i = 0;
	while ((pipes + 1) > i)
	{
		if (ms->cmd[i].cmd)
			free_mem(ms->cmd[i].cmd);
		i++;
	}
}
