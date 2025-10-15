/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:57:41 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/15 16:08:50 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex(unsigned long nb, char c)
{
	char	*hexs;
	int		i;

	if (c == 'x')
		hexs = "0123456789abcdef";
	if (c == 'X')
		hexs = "0123456789ABCDEF";
	i = 0;
	if (nb >= 16)
		i += ft_hex(nb / 16, c);
	i += ftp_putchar_fd(hexs[nb % 16], 1);
	return (i);
}

// int	main(void)
// {
// 	printf(" -> %d\n", ft_hex(74, 'X'));
// 	printf(" -> %d\n", ft_hex(255, 'X'));
// 	printf(" -> %d\n", ft_hex(1024, 'X'));
// 	return (0);
// }

// 1. 74 → 0x4A
// 2. 255 → 0xFF
// 3. 1024 → 0x400