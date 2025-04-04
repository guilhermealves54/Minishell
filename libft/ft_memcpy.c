/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:31:35 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/22 12:31:38 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (0);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}
//
// int main()
// {
// 	int n = 4;
// 	int i = 0;
// 	char src[] = "42porto";
// 	char *dest = src+2;
// 	printf("%s\n", dest);
// 	ft_memcpy(dest, src, n);
// 	printf("%s\n", dest);
// }
