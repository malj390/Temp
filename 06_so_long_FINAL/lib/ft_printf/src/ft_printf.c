/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:56:19 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:04:08 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_var(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ftp_putchar_fd(va_arg(args, int), 1);
	if (c == 's')
		len += ftp_putstr_fd(va_arg(args, char *), 1);
	if (c == 'p')
		len += ft_ptr(va_arg(args, void *));
	if (c == 'd' || c == 'i')
		len += ftp_putnbr_fd(va_arg(args, int), 1);
	if (c == 'u')
		len += ft_putunbr_fd(va_arg(args, unsigned int), 1);
	if (c == 'x' || c == 'X')
		len += ft_hex(va_arg(args, unsigned int), c);
	if (c == '%')
		len += ftp_putchar_fd('%', 1);
	return (len);
}

int	ft_printf(int fd, const char *input, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, input);
	i = 0;
	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			len += get_var(input[i + 1], args);
			i++;
			i++;
		}
		else
		{
			len += ftp_putchar_fd(input[i], fd);
			i++;
		}
	}
	va_end (args);
	return (len);
}
