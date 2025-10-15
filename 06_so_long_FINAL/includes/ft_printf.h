/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:00:32 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 18:39:34 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>

int		ftp_putchar_fd(char c, int fd);
int		ftp_putstr_fd(char *s, int fd);
int		ftp_putnbr_fd(int n, int fd);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_hex(unsigned long nb, char c);
int		ft_ptr(void *ptr);
int		ft_printf(int fd, const char *input, ...);

#endif
