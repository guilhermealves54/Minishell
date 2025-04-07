/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:54:13 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/07 16:06:31 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			update_i(input, &i, input[i]);
			if (!input[i])
			{
				printf("Not closed quotes\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	char_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
