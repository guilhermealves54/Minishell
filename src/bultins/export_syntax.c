/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:52:52 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/09 13:14:28 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_export(char *var, char *content, char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = get_new_str(s);
	if (ft_isdigit(var[i]))
	{
		ft_printf_fd("minishell: export: `%s': not a valid identifier\n", str);
		free_2strings(var, content);
		free(str);
		return (0);
	}
	while (var[i])
	{
		if (!ft_isalnum(var[i]))
		{
			ft_printf_fd(
				"minishell: export: `%s': not a valid identifier\n", str);
			free_2strings(var, content);
			free(str);
			return (0);
		}
		i++;
	}
	return (free(str), 1);
}
