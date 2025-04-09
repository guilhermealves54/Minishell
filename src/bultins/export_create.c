/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:44:33 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/08 20:39:08 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_node(char *var, t_env *head);
static void		append_node(char *var, char *content, t_env *head);
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
	append_node(var, content, mini->export);
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

static void	append_node(char *var, char *content, t_env *head)
{
	t_env	*node;
	t_env	*last;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = content;
	node->var = var;
	node->next = NULL;
	last = ft_last(head);
	node->prev = last;
	last->next = node;
}

static t_env	*find_node(char *var, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(var, head->var) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static t_env	*ft_last(t_env *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}
