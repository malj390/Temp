/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putstr_fd.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:23:20 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:01:09 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		i += ftp_putstr_fd("(null)", fd);
		return (i);
	}
	while (s[i] != '\0')
	{
		ftp_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}

// int	main(void)
// {
// 	ftp_putstr_fd("Yuuuuuuuhu", 1);
// 	return(0);
// }