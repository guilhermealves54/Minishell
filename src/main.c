/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:17 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:20:17 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void	check_argc(int argc, char **argv);

int	main(int argc, char *argv[], char **envp)
{
	t_mini	ms;

	check_argc(argc, argv);
	ms = init(envp);
	while (1)
	{
		ms_signals();
		ms.input = get_input(&ms);
		if (ms.input[0])
		{
			if (check_closed_quotes(ms.input, 1))
			{
				ms.input = expand(ms.input, &ms, 1);
				ms.av = ft_split_redir(ms.input, ' ');
				ms.ap = ft_split_quotes(ms.input, '|');
				if (parsing(&ms))
					execute_cmd(&ms);
				split_memfree(&ms);
			}
		}
		free_2strings(ms.input, ms.prompt);
	}
}

static void	check_argc(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", argv[1]);
		exit(127);
	}
}
