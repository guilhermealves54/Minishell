/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:47:38 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/30 15:15:25 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd(t_mini *ms, int childs, int pipes);
static char	**get_cmd(char	*ap);
static void	input_assign(t_mini *ms, int n, int proc);
static void	init_cmd2(t_mini *ms, int n);

void	execute_cmd(t_mini *ms)
{
	int		proc;
	int		pipes;

	proc = cnt_strings(ms->ap);
	pipes = proc - 1;
	ms->pipes = pipes;
	ms->fds = NULL;
	ms->pid = NULL;
	ms->cmd = ft_calloc(proc, sizeof(t_cmd));
	if (!ms->cmd)
	{
		ft_printf_fd(2, "minishell: error allocating memory\n");
		exit(exec_free(ms, pipes, FREE_BASE, 1));
	}
	if (pipes > 0)
		ms->fds = crt_pipes(ms, pipes);
	init_cmd(ms, proc, pipes);
	if (pidnbr_cnt(ms, proc) > 0)
		ms->pid = crt_pid_arr(ms, pidnbr_cnt(ms, proc), pipes);
	fork_proc(ms, proc, pipes);
}

static void	init_cmd(t_mini *ms, int proc, int pipes)
{
	int		n;

	n = 0;
	while (n < proc)
	{
		ms->cmd[n].index = n;
		ms->cmd[n].cmd = get_cmd(ms->ap[n]);
		if (!ms->cmd[n].cmd)
		{
			ft_printf_fd(2, "minishell: error allocating memory\n");
			exit(exec_free(ms, n, FREE_BASE | FREE_STRUCT | FREE_FDS
					| FREE_PIPES, 1));
		}
		if (pipes > 0)
			input_assign(ms, n, proc);
		else
		{
			ms->cmd[n].input_fd = STDIN_FILENO;
			ms->cmd[n].output_fd = STDOUT_FILENO;
		}
		init_cmd2(ms, n);
		n++;
	}
}

static void	init_cmd2(t_mini *ms, int n)
{
	ms->cmd[n].sts = 0;
	ms->cmd[n].redirin = -1;
	ms->cmd[n].redirout = -1;
	ms->cmd[n].cmd = exec_redir(ms, n);
	if (!ms->cmd[n].cmd)
		ms->cmd[n].builtin = 0;
	if (ms->cmd[n].cmd)
	{
		ms->cmd[n].path = ms->cmd[n].cmd[0];
		ms->cmd[n].builtin = check_cmd(ms->cmd[n].cmd[0]);
	}
}

static char	**get_cmd(char	*ap)
{
	char	*temp;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_redir(ap, ' ');
	while (cmd[i] && !check_cmd(cmd[i]) && !is_redir(cmd[i]))
	{
		temp = cmd[i];
		cmd[i] = get_new_str(cmd[i]);
		free(temp);
		i++;
	}
	return (cmd);
}

static void	input_assign(t_mini *ms, int n, int proc)
{
	if (n == 0)
		ms->cmd[n].input_fd = STDIN_FILENO;
	else
		ms->cmd[n].input_fd = ms->fds[n - 1][0];
	if (n == proc - 1)
		ms->cmd[n].output_fd = STDOUT_FILENO;
	else
		ms->cmd[n].output_fd = ms->fds[n][1];
}
