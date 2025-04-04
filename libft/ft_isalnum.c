/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:36:25 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/18 11:36:28 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}
//
// #include <stdio.h>
// #include <ctype.h>
//
// int main()
// {
// 	printf("%i\n", ft_isalnum(58));
// 	printf("%i\n", ft_isalnum('0'));
// 	printf("%i\n", ft_isalnum('\n'));	
// }
