/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:09:40 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/21 17:44:29 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "minishell.h"

static int	pf_print(va_list *ap, char spec, int count, int fd);
static int	ft_putchar(int c, int fd);
static int	ft_putstr(char *str, int fd);
static int	ft_putnbr(long n, int base, int count, int cap, int fd);

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += pf_print(&ap, format[++i], 0, fd);
		}
		else
			count += ft_putchar(format[i], fd);
		i++;
	}
	va_end(ap);
	return (count);
}

static int	pf_print(va_list *ap, char spec, int count, int fd)
{
	if (spec == 'c')
		count = ft_putchar(va_arg(*ap, int), fd);
	else if (spec == '%')
		count = ft_putchar('%', fd);
	else if (spec == 's')
		count = ft_putstr(va_arg(*ap, char *), fd);
	else if (spec == 'i' || spec == 'd')
		count = ft_putnbr(va_arg(*ap, int), 10, 0, 0, fd);
	else if (spec == 'u')
		count = ft_putnbr(va_arg(*ap, unsigned int), 10, 0, 0, fd);
	else if (spec == 'x')
		count = ft_putnbr(va_arg(*ap, unsigned int), 16, 0, 0, fd);
	else if (spec == 'X')
		count = ft_putnbr(va_arg(*ap, unsigned int), 16, 0, -32, fd);
	return (count);
}

static int	ft_putchar(int c, int fd)
{
	return (write(fd, &c, 1));
}

static int	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(fd, str, 1);
		str++;
		i++;
	}
	return (i);
}

static int	ft_putnbr(long n, int base, int count, int cap, int fd)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n < 0)
	{
		count += ft_putchar('-', fd);
		n = -n;
	}
	if (n < base)
	{
		if (n > 9)
			count += ft_putchar(hexa[n] + cap, fd);
		else
			count += ft_putchar(hexa[n], fd);
	}
	else
	{
		count += ft_putnbr(n / base, base, 0, cap, fd);
		count += ft_putnbr(n % base, base, 0, cap, fd);
	}
	return (count);
}
