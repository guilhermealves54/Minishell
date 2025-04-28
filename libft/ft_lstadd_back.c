/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:33:01 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/29 18:33:04 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
int main()
{
	t_list *new = ft_lstnew("porto");
	t_list *lst = ft_lstnew("rui");
	lst->next = ft_lstnew("campos");
	printf("%s\n", (char *)ft_lstlast(lst)->content);
	ft_lstadd_back(&lst, new);
	printf("%s\n", (char *)ft_lstlast(lst)->content);	
}
*/