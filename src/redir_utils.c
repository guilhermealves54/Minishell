/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:37:36 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/24 17:39:16 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, ">>", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, "<", 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, ">", 1) == 0)
	{
		return (1);
	}
	return (0);
}

int	white_spaces(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}
