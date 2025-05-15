/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:44:33 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/15 00:05:07 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_node(char *var, t_env *head);
static void		append_node(char *var, char *content, t_env *head, t_mini *ms);
static t_env	*ft_last(t_env *head);
static void		update_content(char *var, char *content, t_env *export, char c);

void	create_export(char *var, char *content, t_mini *mini, char c)
{
	t_env	*export;

	export = find_node(var, mini->export);
	if (export)
	{
		update_content(var, content, export, c);
		return ;
	}
	append_node(var, content, mini->export, mini);
}

static void	update_content(char *var, char *content, t_env *export, char c)
{
	char	*temp;

	temp = export->content;
	if (content)
	{
		if (c == '+' && temp)
		{
			export->content = ft_strjoin(temp, content);
			free_2strings(temp, content);
		}
		else
		{
			export->content = content;
			free(temp);
		}
		free(var);
		return ;
	}
	free_2strings(var, content);
	return ;
}

static void	append_node(char *var, char *content, t_env *head, t_mini *ms)
{
	t_env	*node;
	t_env	*last;
	char	*temp;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = content;
	temp = ft_strjoin("\"", content);
	node->content_qts = ft_strjoin(temp, "\"");
	free(temp);
	node->var = var;
	node->next = NULL;
	last = ft_last(head);
	if (last)
	{
		node->prev = last;
		last->next = node;
	}
	else
	{
		node->prev = NULL;
		ms->export = node;
	}
}

static t_env	*find_node(char *var, t_env *head)
{
	t_env	*node;

	node = head;
	while (node)
	{
		if (ft_strcmp(var, node->var) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

static t_env	*ft_last(t_env *head)
{
	t_env	*node;

	node = head;
	while (node && node->next)
		node = node->next;
	return (node);
}
