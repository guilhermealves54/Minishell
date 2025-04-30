/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:38:21 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/30 15:19:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_redir(char *s, char *file, t_mini *ms, int n);
static int	openfile(char *file, int option, t_mini *ms, int n);
static int	do_redir(t_mini *ms, int n, int *i);
static void	update_fds(t_mini *ms, int n, int option, int fd);

char	**exec_redir(t_mini *ms, int n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ms->redirap = malloc(sizeof(char *) * (cnt_strings(ms->cmd[n].cmd) + 1));
	if (!ms->redirap)
		return (NULL);
	g_exit_status = 0;
	while (ms->cmd[n].cmd[i] && g_exit_status != 130)
	{
		ms->redirap[j] = NULL;
		if (is_redir(ms->cmd[n].cmd[i]))
		{
			if (!do_redir(ms, n, &i))
				return (NULL);
		}
		else
			ms->redirap[j++] = ft_strdup(ms->cmd[n].cmd[i++]);
	}
	ms->redirap[j] = NULL;
	free_mem(ms->cmd[n].cmd);
	return (ms->redirap);
}

static int	do_redir(t_mini *ms, int n, int *i)
{
	if (!execute_redir(ms->cmd[n].cmd[*i], ms->cmd[n].cmd[*i + 1], ms, n))
	{
		free_mem(ms->redirap);
		free_mem(ms->cmd[n].cmd);
		return (0);
	}
	*i += 2;
	return (1);
}

static int	execute_redir(char *s, char *file, t_mini *mini, int n)
{
	int	fd;

	if (!file)
		return (0);
	if (ft_strcmp(s, "<<"))
		file = get_new_str(file);
	fd = 0;
	if (ft_strncmp(s, "<<", 2) == 0)
	{
		here_doc(mini, file, n);
		return (1);
	}
	else if (ft_strncmp(s, "<", 1) == 0)
		fd = openfile(file, 0, mini, n);
	else if (ft_strncmp(s, ">>", 2) == 0)
		fd = openfile(file, 2, mini, n);
	else if (ft_strncmp(s, ">", 1) == 0)
		fd = openfile(file, 1, mini, n);
	free(file);
	return (fd);
}

// OPEN FILE
// 0-RD_ONLY   1-WR_ONLY   2-APPEND
static int	openfile(char *file, int option, t_mini *ms, int n)
{
	int	fd;

	fd = 0;
	if (option == 0)
		fd = open(file, O_RDONLY);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", file, strerror(errno));
		g_exit_status = 1;
		return (0);
	}
	else
		update_fds(ms, n, option, fd);
	return (1);
}

static void	update_fds(t_mini *ms, int n, int option, int fd)
{
	if (option == 0)
	{
		ms->cmd[n].input_fd = fd;
		if (ms->cmd[n].redirin != -1)
			close(ms->cmd[n].redirin);
		ms->cmd[n].redirin = fd;
	}
	else
	{
		ms->cmd[n].output_fd = fd;
		if (ms->cmd[n].redirout != -1)
			close(ms->cmd[n].redirout);
		ms->cmd[n].redirout = fd;
	}
}
