/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:30:46 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/17 17:30:49 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main()
{
	printf("%i\n", ft_isalpha(90));
	printf("%i\n", ft_isalpha('B'));
	printf("%i\n", isalpha('k'));	
}
*/
