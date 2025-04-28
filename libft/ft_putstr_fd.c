/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:44:26 by ruida-si          #+#    #+#             */
/*   Updated: 2024/10/29 12:44:29 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, &*s++, 1);
}
/*
#include <fcntl.h>

int main()
{
	int fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error open file");
		return (1);
	}
	char s[] = "rui campos";
	ft_putstr_fd(s, fd);	
	if (close(fd) == -1)
	{
		perror("Error close file");
		return (1);
	}
}
*/