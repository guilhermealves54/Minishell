/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:38:51 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/28 13:38:58 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	free_mem(char **array, int string)
{
	while (string >= 0)
	{
		free(*(array + string));
		string--;
	}
	free(array);
}

static char	**do_split(char const *s, char **array, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			array[j] = ft_substr(s + i, 0, length(s + i, c));
			if (!array[j])
			{
				free_mem(array, j);
				return (NULL);
			}
			j++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!array)
		return (NULL);
	array = do_split(s, array, c);
	return (array);
}
/*
int main()
{
	char s[] = "123 456";
	char c = ' ';
	char **array = ft_split(s, c);
	int i = 0;
	while (array && array[i])
	{
		printf(".%s.\n", array[i]);
		i++;
	}

	while (i-- > 0)
	{
			printf ("%d\n", i);
			free (array[i]);
	}
	free(array);
}
*/