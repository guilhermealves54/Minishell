/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:22:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/26 16:13:54 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_quotes(char *file, int *a);
static void	update_fds(t_mini *ms, int n, int fd);

void	here_doc(t_mini *ms, char *file, int n)
{
	char	*s;
	int		fd[2];
	int		quotes;

	file = check_quotes(file, &quotes);
	pipe(fd);
	while (1)
	{
		s = readline("> ");
		if (!s)
			break ;
		if (ft_strcmp(file, s) == 0)
		{
			free(s);
			break ;
		}
		if (!quotes)
			s = expand(s, ms, 0);
		write(fd[1], s, ft_strlen(s));
		write(fd[1], "\n", 1);
		free(s);
	}
	free(file);
	close(fd[1]);
	update_fds(ms, n, fd[0]);
}

static void	update_fds(t_mini *ms, int n, int fd)
{
	ms->cmd[n].input_fd = fd;
	if (ms->cmd[n].redirin != -1)
		close(ms->cmd[n].redirin);
	ms->cmd[n].redirin = fd;
}

static char	*check_quotes(char *file, int *quotes)
{
	char	*s;

	if (file[0] == '\"' || file[0] == '\'')
	{
		*quotes = 1;
		s = get_new_str(file);
		return (s);
	}
	*quotes = 0;
	return (ft_strdup(file));
}
