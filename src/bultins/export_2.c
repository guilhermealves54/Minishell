/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:13:54 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/11 15:33:10 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_slash(char *s, int j);

char	*check_content(char *content)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = get_new_str(content);
	free(content);
	while (temp[i])
	{
		if (temp[i] == '$')
			j++;
		i++;
	}
	if (j > 0)
		temp = add_slash(temp, j);
	return (temp);
}

static char	*add_slash(char *s, int j)
{
	int		i;
	char	*str;

	i = ft_strlen(s) + j + 1;
	str = malloc(i);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
			str[j++] = '\\';		
		str[j++] = s[i++];
	}
	str[j] = '\0';
	free(s);
	return (str);
}
