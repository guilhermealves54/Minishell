/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:24:08 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/29 13:24:46 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the last char of split for spaces
char	get_last_char(t_mini *mini)
{
	char	**av;
	int		i;
	int		j;
	char	c;

	i = 0;
	av = mini->av;
	if (!av || !av[0])
		return ('\0');
	while (av[i])
		i++;
	j = ft_strlen(av[--i]);
	c = av[i][--j];
	return (c);
}
