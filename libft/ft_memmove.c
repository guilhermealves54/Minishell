/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:55:30 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/22 13:55:44 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (0);
	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			((char *)dest)[n] = ((const char *)src)[n];
	}
	return (dest);
}
//
// int main()
// {
// 	char src[] = "42porto";
// 	char *dest = src+2;
// 	int n = 3;
// 	printf("%s\n", dest);
// 	memcpy(dest, src, n);
// 	printf("%s\n", dest);
// }
