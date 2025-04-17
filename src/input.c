/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:39 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/17 15:47:23 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(void);
static void	eof_exit(t_mini *ms);
static char	*add_color(char *cwd, char *color);

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
	char	*temp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	cwd = add_color(cwd, BLUE);
	temp = ft_strjoin_3(cwd, GREEN "Minishell$" RESET, '@');
	prompt = ft_strjoin(temp, " ");
	free_2strings(cwd, temp);
	return (prompt);
}

static void	eof_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	free(ms->prompt);
	exit(0);
}

static char	*add_color(char *cwd, char *color)
{
	char	*s;
	char	*s2;

	s = ft_strjoin(color, cwd);
	s2 = ft_strjoin(s, RESET);
	free_2strings(s, cwd);
	return (s2);
}
