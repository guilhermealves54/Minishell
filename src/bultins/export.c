/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:40:09 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/08 20:40:57 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_env	*head);
static void	extract_export(char *s, t_mini *ms);
static char	*get_content(char *s, int i);

void	exec_export(t_mini *ms)
{
	int	i;

	i = 1;
	order_envp(ms);
	if (!ms->av[1])
		print_export(ms->export);
	while (ms->av[i])
	{
		extract_export(ms->av[i], ms);
		i++;
	}
}

static void	print_export(t_env	*head)
{
	while (head)
	{
		if (!head->content)
			printf("declare -x %s\n", head->var);
		else
			printf("declare -x %s=\"%s\"\n", head->var, head->content);
		head = head->next;
	}
}

static void	extract_export(char *s, t_mini *ms)
{
	char	*var;
	char	*content;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=' && ft_strncmp(s + i, "+=", 2) != 0)
		i++;
	var = get_str(s, 0, i);
	if (!s[i])		
		content = NULL;
	else
		content = get_content(s, i);
	if (syntax_export(var, content, s))
		create_export(var, content, ms, s[i]);
}

static char	*get_content(char *s, int i)
{
	char	*content;
	
	if (s[i] == '+')
		content = get_str(s, i + 2, ft_strlen(s));
	else
		content = get_str(s, i + 1, ft_strlen(s));
	content = check_content(content);
	return (content);
}
