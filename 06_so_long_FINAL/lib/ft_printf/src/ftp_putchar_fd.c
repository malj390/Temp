/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:54:17 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/05/15 12:38:27 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_putchar_fd(char c, int fd)
{
	int	i;

	i = 0;
	i += write(fd, &c, 1);
	return (i);
}

// int	main(void)
// {
// 	ftp_putchar_fd('a', 1);
// 	return(0);
// }