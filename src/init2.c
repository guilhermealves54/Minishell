/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:36 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/04 18:29:20 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpid(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_printf_fd("Failed fork");
	if (pid == 0)
		exit(0);
	wait(0);
	return (pid - 1);
}
