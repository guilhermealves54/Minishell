/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:55:30 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/06 13:54:33 by ruida-si         ###   ########.fr       */
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
