/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:09:00 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/30 13:09:02 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void test(void *content)
{	
	ft_strlcpy((char *)content, "porto", 10);
}

int main()
{
	t_list *node;
	node = ft_lstnew(ft_strdup("rui"));
	node->next = ft_lstnew(ft_strdup("campos"));
	printf("%s\n", (char *)node->content);
	printf("%s\n", (char *)node->next->content);
	ft_lstiter(node, test);
	printf("%s\n", (char *)node->content);
	printf("%s\n", (char *)node->next->content);
}
*/