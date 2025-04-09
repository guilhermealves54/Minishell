/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:17:46 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/09 16:24:51 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd()
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		perror("Pwd error");
		return ;
	}
	printf("%s\n", s);
	free(s);
	return ;
}
