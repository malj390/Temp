/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putnbr_fd.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:54:37 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:38:36 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_putnbr_fd(int n, int fd)
{
	long	nb;
	int		i;

	nb = n;
	i = 0;
	if (nb < 0)
	{
		i += ftp_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
		i += ftp_putnbr_fd(nb / 10, fd);
	i += ftp_putchar_fd((nb % 10) + '0', fd);
	return (i);
}
// int	main(void)
// {
// 	// ftp_putnbr_fd(123456, 1);
// 	printf("%d", count_numbers(123));
// 	return(0);
// }