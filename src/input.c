/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:39 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/14 13:04:52 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(void);
static void	eof_exit(t_mini *ms);

char	*get_input(t_mini *ms)
{
	char	*input;

	ms->prompt = get_prompt();
	input = readline(ms->prompt);
	if (!input)
		eof_exit(ms);
	if (input[0])
		add_history(input);
	return (input);
}

static char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin_3(cwd, "Minishell$ ", '@');
	free(cwd);
	return (prompt);
}

static void	eof_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	free(ms->prompt);
	exit(0);
}
