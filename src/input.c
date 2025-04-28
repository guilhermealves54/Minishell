/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:39 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/25 17:36:44 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(t_mini *ms);
static void	eof_exit(t_mini *ms);
static char	*add_color(char *cwd, char *color);

char	*get_input(t_mini *ms)
{
	char	*input;

	ms->prompt = get_prompt(ms);
	input = readline(ms->prompt);
	if (!input)
		eof_exit(ms);
	if (input[0])
		add_history(input);
	return (input);
}

static char	*get_prompt(t_mini *ms)
{
	char	*cwd;
	char	*temp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		cwd = add_color(cwd, BLUE);
		temp = ft_strjoin_3(cwd, GREEN "Minishell$" RESET, '@');
		prompt = ft_strjoin(temp, " ");
		free_2strings(cwd, temp);
	}
	else
	{
		cwd = ft_getenv("PWD", ms);
		if (!cwd)
			return (ft_strjoin(GREEN "Minishell$" RESET, " "));
		cwd = add_color(ft_strdup(cwd), BLUE);
		temp = ft_strjoin_3(cwd, GREEN "Minishell$" RESET, '@');
		prompt = ft_strjoin(temp, " ");
		free_2strings(cwd, temp);
	}
	return (prompt);
}

static void	eof_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	free(ms->prompt);
	exit(0);
}

// add color to a string
static char	*add_color(char *cwd, char *color)
{
	char	*s;
	char	*s2;

	if (!cwd)
		return (NULL);
	s = ft_strjoin(color, cwd);
	s2 = ft_strjoin(s, RESET);
	free_2strings(s, cwd);
	return (s2);
}
