/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:11:15 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/29 13:11:18 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(fd, &*s++, 1);
	write(fd, "\n", 1);
}
/*
#include <fcntl.h>

int main()
{
	int fd = open("test", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error open file");
		return (1);
	}
	char s[] = "42porto";
	ft_putendl_fd(s, fd);
	if (close(fd) == -1)
	{
		perror("Error close file");
		return (1);
	}
}
*/