/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:36:26 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/24 11:36:28 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*lit == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == lit[j])
		{
			while (big[i + j] == lit[j] && lit[j] && (i + j) < len)
				j++;
			if (!lit[j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char b[] = "42porto";
	char lit[] = "rt";
	int len = 5;
	printf("%s\n", ft_strnstr(b, lit, len));
}
*/
