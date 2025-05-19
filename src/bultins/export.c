/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:40:09 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/15 10:27:57 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_mini *ms, t_env	*head, int n);
static int	extract_export(char *s, t_mini *ms);
static char	*get_content(char *s, int i);

int	exec_export(t_mini *ms, char **av, int np)
{
	int	i;
	int	n;
	int	a;

	i = 1;
	n = 0;
	order_envp(ms);
	if (!av[i])
		print_export(ms, ms->export, np);
	if (cnt_strings(ms->ap) > 1)
		return (1);
	while (av[i])
	{
		a = extract_export(av[i], ms);
		if (a == 1)
			n = 1;
		i++;
	}
	return (n);
}

static void	print_export(t_mini *ms, t_env	*head, int n)
{
	int	fd;

	fd = ms->cmd[n].output_fd;
	while (head)
	{
		if (!head->content)
			ft_printf_fd(fd, "declare -x %s\n", head->var);
		else
			ft_printf_fd(fd,
				"declare -x %s=\"%s\"\n", head->var, head->content);
		head = head->next;
	}
}

static int	extract_export(char *s, t_mini *ms)
{
	char	*var;
	char	*content;
	int		i;

	i = 0;
	if (s[i] == '=' || ft_strncmp(s, "+=", 2) == 0)
	{
		ft_printf_fd(2,
			"minishell: export: `%s': not a valid identifier\n", s);
		return (1);
	}
	while (s[i] && s[i] != '=' && ft_strncmp(s + i, "+=", 2) != 0)
		i++;
	var = get_str(s, 0, i);
	if (!s[i])
		content = NULL;
	else
		content = get_content(s, i);
	if (syntax_export(var, content, s, 0))
	{
		create_export(var, content, ms, s[i]);
		return (0);
	}
	return (1);
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
