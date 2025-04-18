/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:38:21 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/18 16:43:19 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_redir(char *s, char *file, t_mini *ms, int n);
static int	is_redir(char *s);
static int	openfile(char *file, int option, t_mini *ms, int n);

char	**exec_redir(t_mini *ms, int n)
{
	char	**ap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ap = malloc(sizeof(char *) * (cnt_strings(ms->cmd[n].cmd) + 1));
	if (!ap)
		return (NULL);	
	while (ms->cmd[n].cmd[i])
	{
		ap[j] = NULL;
		if (is_redir(ms->cmd[n].cmd[i]))
		{
			if (!execute_redir(ms->cmd[n].cmd[i], ms->cmd[n].cmd[i + 1], ms, n))
			{
				free_mem(ap);
				free_mem(ms->cmd[n].cmd);
				return (NULL);
			}
			i+= 2;
		}
		else
			ap[j++] = ft_strdup(ms->cmd[n].cmd[i++]);
	}
	ap[j] = NULL;
	free_mem(ms->cmd[n].cmd);
	return (ap);
}

static int	is_redir(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, ">>", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, "<", 1) == 0)
	{
		return (1);		
	}		
	else if (ft_strncmp(s, ">", 1) == 0)
	{
		return (1);		
	}
	return (0);
}

static int	execute_redir(char *s, char *file, t_mini *mini, int n)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(s, "<<", 2) == 0)
		fd = openfile(file, 0, mini, n);
	else if (ft_strncmp(s, "<", 1) == 0)
		fd = openfile(file, 0, mini, n);
	else if (ft_strncmp(s, ">>", 2) == 0)
		fd = openfile(file, 2, mini, n);
	else if (ft_strncmp(s, ">", 1) == 0)
		fd = openfile(file, 1, mini, n);
	return (fd);
}

// OPEN FILE
// 0-RD_ONLY   1-WR_ONLY   2-APPEND
static int	openfile(char *file, int option, t_mini *ms, int n)
{
	int fd;

	fd = 0;
	if (option == 0)
		fd = open(file, O_RDONLY);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf_fd("minishell: %s: %s\n", file, strerror(errno));
		return (0);
	}
	else
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
	return (1);
}
