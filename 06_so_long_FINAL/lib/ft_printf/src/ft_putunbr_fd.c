/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:37:30 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:38:24 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned int	nb;
	int				i;

	nb = n;
	i = 0;
	if (nb < 0)
	{
		i += ftp_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
		i += ft_putunbr_fd(nb / 10, fd);
	i += ftp_putchar_fd((nb % 10) + '0', fd);
	return (i);
}
// int	main(void)
// {
// 	// ftp_putnbr_fd(123456, 1);
// 	printf("%d", count_numbers(123));
// 	return(0);
// }