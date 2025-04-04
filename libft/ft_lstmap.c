/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:14:27 by ruida-si          #+#    #+#             */
/*   Updated: 2024/11/01 15:11:47 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_lst(t_list *lst, void *(*f)(void *),
							void (*del)(void *))
{
	t_list	*new;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	new = ft_lstnew(content);
	if (!new)
	{
		del(content);
		return (NULL);
	}
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*mem;

	head = create_lst(lst, f, del);
	if (!head)
		return (NULL);
	new = head;
	lst = lst->next;
	while (lst)
	{
		mem = f(lst->content);
		new->next = ft_lstnew(mem);
		if (!new->next)
		{
			del(mem);
			ft_lstclear(&head, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (head);
}
