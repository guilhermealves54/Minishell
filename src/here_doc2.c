/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:53:58 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/15 12:54:20 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_eof(char *file, char *buff)
{
	if (ft_strncmp(file, buff, ft_strlen(buff) - 1) == 0
		&& ft_strncmp(file, buff, ft_strlen(file)) == 0)
		return (1);
	return (0);
}
