/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:50:05 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/18 11:50:08 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
// 	printf("%i\n", ft_isascii(-1));
// 	printf("%i\n", ft_isascii('B'));
// 	printf("%i\n", ft_isascii('k'));	
// }
