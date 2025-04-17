/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:38:21 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/17 19:31:08 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_redir(char *s, char *file, t_mini *mini);
static int	is_redir(char *s);
static int	openfile(char *file, int option, t_mini *mini);

char	**exec_redir(char **av, t_mini *mini)
{
	char	**ap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ap = malloc(sizeof(char *) * (cnt_strings(av) + 1));
	if (!ap)
		return (NULL);	
	while (av[i])
	{
		if (is_redir(av[i]))
		{
			if (!execute_redir(av[i], av[i + 1], mini))
			{
				return (NULL);
			}
			i+= 2;
		}
		else
			ap[j++] = ft_strdup(av[i++]);
	}
	ap[j] = NULL;
//	free_mem(av);
	return (ap);
}

static int	is_redir(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
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

static int	execute_redir(char *s, char *file, t_mini *mini)
{
	int	fd;

	fd = 0;	
	if (ft_strncmp(s, "<", 1) == 0)
		fd = openfile(file, 0, mini);
	else if (ft_strncmp(s, ">>", 2) == 0)
		fd = openfile(file, 2, mini);
	else if (ft_strncmp(s, ">", 1) == 0)
		fd = openfile(file, 1, mini);
	return (fd);
}

// OPEN FILE
// 0-RD_ONLY   1-WR_ONLY   2-APPEND
static int	openfile(char *file, int option, t_mini *mini)
{
	int fd;

	fd = 0;	
	(void)mini;
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
			close(STDIN_FILENO);
		else
			close(STDOUT_FILENO);
		dup (fd);
		close(fd);
	}
	return (1);
}
