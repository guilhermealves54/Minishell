/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:40:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/10 17:52:35 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	free(ms->prompt);
	split_memfree(ms);
	exit(0); 
}
