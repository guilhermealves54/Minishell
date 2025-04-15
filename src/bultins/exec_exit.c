/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:40:10 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/15 18:24:24 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(t_mini *ms)
{
	printf("exit\n");
	clean_list(ms);
	free_2strings(ms->prompt, ms->input);
	split_memfree(ms);
	exit(exec_free(ms, 0, FREE_STRUCT | FREE_CMD, 0));
}
