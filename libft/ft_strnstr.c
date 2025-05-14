/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:36:26 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/14 20:26:51 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_new_str(char *s);
static void	new_str(char *str, char *s, int *i, int *j);

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
