/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:32 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/14 23:44:25 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_envp(char **envp);
static void		create_node(t_env **head, char *s);
static char		*get_var(char *s);
static t_env	*ft_last(t_env *head);

t_mini	init(char **envp)
{
	t_mini	ms;

	ms.ppid = ft_getpid();
	ms.input = NULL;
	ms.export = get_envp(envp);
	ms.envp = envp;
	ms.childrun = 0;
	g_exit_status = 0;
	return (ms);
}

static t_env	*get_envp(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		create_node(&head, envp[i]);
		i++;
	}
	return (head);
}

static void	create_node(t_env **head, char *s)
{
	t_env	*node;
	t_env	*last;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->var = get_var(s);
	node->content = ft_strdup(s + ft_strlen(node->var) + 1);
	node->content_qts = ft_strdup(s + ft_strlen(node->var) + 1);
	node->next = NULL;
	if (!(*head))
	{
		*head = node;
		node->prev = NULL;
	}
	else
	{
		last = ft_last(*head);
		node->prev = last;
		last->next = node;
	}
}

static char	*get_var(char *s)
{
	int		i;
	char	*var;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '=')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (s[i] != '=')
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

static t_env	*ft_last(t_env *head)
{
	t_env	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current && current->next)
		current = current->next;
	return (current);
}
