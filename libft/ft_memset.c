/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:35 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/18 16:28:19 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		*str++ = (unsigned char)c;
		n--;
	}
	return (s);
}
//
// int main()
// {
// 	int str[] = {1, 2};
// 	int c = 68;
// 	int a = 5;
// 	printf("%s\n", (char *)ft_memset(str, c, a));
// 	puts(memset(str, c, a));
// }
