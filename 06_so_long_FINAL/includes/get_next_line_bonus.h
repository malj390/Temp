/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:04:02 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/01 17:44:47 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_Index
{
	ssize_t		readed;
	size_t		i;
	size_t		j;
	size_t		jump;
	size_t		total;
}	t_Index;

// get_next_line.c
char	*ft_free(char *buffer);
size_t	ft_strlen_char(const char *str, char c);
char	*update_stash(char *stash);
char	*extract_line(char *stash);
char	*get_next_line(int fd);

// get_next_line_utils.c
void	*ft_gnl_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_gnl_strchr(const char *s, int c);
char	*read_line(int fd, char *stash);

#endif