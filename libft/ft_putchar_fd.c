/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:26:44 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/28 18:26:46 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <fcntl.h>

int main()
{
	int fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
        perror("Error opening file");
        return 1;
    }
	ft_putchar_fd('0', fd);
	printf("%i\n", fd);
	close(fd);
}
*/