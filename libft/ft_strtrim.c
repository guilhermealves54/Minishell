/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:20 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/28 11:56:24 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]) && i <= len)
		i++;
	if (i <= len)
	{
		while (ft_strchr(set, s1[len]))
			len--;
	}
	new = malloc(len - i + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1 + i, len - i + 2);
	return (new);
}
/*
int main()
{
	char s[] = "ruicui";
	char set[] = "rui";
	printf(".%s.\n", ft_strtrim(s, set));
}
*/