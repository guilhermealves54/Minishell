/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:36:40 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/19 15:36:44 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (n-- > 0)
		*ptr++ = 0;
}
//
// int main()
// {
// 	char str[] = "Rui Campos";
// 	int n = 6;
// 	int i = 0;
// 	int len = ft_strlen(str);
// 	printf("%s\n", str);
// 	ft_bzero(str, n);
// 	while (i < len)
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// }
