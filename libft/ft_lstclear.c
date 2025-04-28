/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:15:09 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/30 12:15:12 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
void del(void *node)
{
	node = NULL;
}
int main()
{
	t_list *node;
	
	node = ft_lstnew("rui");
	node->next = ft_lstnew("porto");
	printf("%s\n", (char *)node->content);
	if (node)
		printf("yes\n");
	ft_lstclear(&node, del);
	if (!node)
		printf("nothing to print\n");
}
*/