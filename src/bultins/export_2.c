/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:13:54 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/10 18:51:10 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_slash(char *s, int j);
static int	is_slash(char c);

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
		else if (s[i] == '\\' && !is_slash(s[i +1]) && s[i +1])
			i++;
		str[j++] = s[i++];
	}
	str[j] = '\0';
	free(s);
	return (str);
}

static int	is_slash(char c)
{
	if (c == '\\')
		return (1);
	return (0);
}
