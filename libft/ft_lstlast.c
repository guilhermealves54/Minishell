/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:07:01 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/29 18:07:03 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}
/*
int main()
{
	t_list *n1 = ft_lstnew("rui");
	n1->next = ft_lstnew("campos");
	printf("%s\n", (char *)ft_lstlast(n1)->content);
}
*/