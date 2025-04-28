/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:46:24 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/23 13:46:27 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	if ((char)c == 0)
		return ((char *)str + len);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return ((char *)str + len);
		len--;
	}
	return (NULL);
}
/*
int main()
{
	char str[] = "42 porto";
	int c = 0;
	printf("%s\n", ft_strrchr(str, c));
	printf("%s\n", strrchr(str, c));
}
*/
