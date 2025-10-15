/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:55 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:04:23 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr(void *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
	{
		i += ftp_putstr_fd("(nil)", 1);
		return (i);
	}
	i += ftp_putstr_fd("0x", 1);
	i += ft_hex((unsigned long)ptr, 'x');
	return (i);
}

// int	main(void)
// {
// 	int		x = 42;
// 	int		*ptr = &x;
// 	int		printed;

// 	printed = ft_ptr(ptr);
// 	ftp_putstr_fd("\n", 1);
// 	printf("printf %d\n", printed);
// 	// ft_printf("ft_printf %d\n", printed);
// 	return (0);
// }
