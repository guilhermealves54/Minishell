/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:58:18 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/28 11:58:24 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
void	test(unsigned int i, char *s)
{
	if (i % 2 == 0)
		s[0] = ft_toupper(s[0]);
}

int main()
{
	char s[] = "rui campos";
	ft_striteri(s, test);
	printf(".%s.\n", s);
}
*/