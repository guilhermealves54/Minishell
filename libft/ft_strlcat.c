/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:48 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/22 17:12:53 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s;
	size_t	d;
	size_t	j;
	size_t	i;

	s = ft_strlen(src);
	d = ft_strlen(dst);
	if (size <= d)
		return (size + s);
	j = 0;
	i = d;
	while (src[j] && i < size -1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (d + s);
}
//
// int main()
// {
// 	char dst[] = "Rui";
// 	char src[] = "C";
// 	size_t n = 7;
// 	printf("%s\n", dst);
// 	ft_strlcat(dst, src, n);
// 	printf("%s\n", dst);
// }
