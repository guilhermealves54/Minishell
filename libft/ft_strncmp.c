/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:36:05 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/23 14:36:08 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && i < n && (str1[i] == str2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
/*
int main()
{
	char s1[] = "Rui der";
	char s2[] = "Ru";
	int n = 3;
	printf("%i\n", ft_strncmp(s1, s2, n));
	printf("%i\n", strncmp(s1, s2, n));
}
*/
