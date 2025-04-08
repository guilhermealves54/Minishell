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

volatile sig_atomic_t	g_childrun;

static void	check_argc(int argc, char **argv);
static void	eof_exit(t_mini *ms);

int	main(int argc, char *argv[], char **envp)
{
	t_mini	ms;

	check_argc(argc, argv);
	ms = init(envp);
	g_childrun = 0;
	setup_signals();
	while (1)
	{
		ms.input = get_input(ms.prompt);
		if (!ms.input)
			eof_exit(&ms);
		if (ms.input[0])
		{
			if (check_closed_quotes(ms.input))
			{
				ms.input = expand(ms.input, &ms);
				ms.av = ft_split_quotes(ms.input, ' ');
				ms.ap = ft_split_quotes(ms.input, '|');
				if (parsing(&ms))
					execute_cmd(&ms);
				split_memfree(&ms);
			}
		}
		free(ms.input);
	}
}

static void	check_argc(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_printf_fd("minishell: %s: No such file or directory\n", argv[1]);
		exit(127);
	}
}

static void	eof_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	exit(0);
}
