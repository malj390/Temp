/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:58:45 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/01 17:45:22 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_gnl_calloc(size_t nmemb, size_t size)
{
	unsigned char	*array;
	size_t			i;

	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	if (nmemb == 0)
		return (array);
	i = 0;
	while (i < nmemb * size)
	{
		array[i] = 0;
		i++;
	}
	return ((unsigned char *)array);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen_char(s, '\0');
	if (start > size)
		len = 0;
	if (len > size - start)
		len = size - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i]; 
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char		*str;
	t_Index		index;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen_char(s2, '\0') + \
ft_strlen_char(s1, '\0') + 1));
	if (!str)
		return (ft_free(str));
	index.i = 0;
	index.j = 0;
	while (s1[index.i] != '\0')
	{
		str[index.i] = s1[index.i];
		index.i++;
	}
	while (s2[index.j] != '\0')
	{
		str[index.i + index.j] = s2[index.j];
		index.j++;
	}
	str[index.i + index.j] = '\0';
	free((char *)s1);
	return (str);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*str;

	cc = (char )c;
	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
			return (&str[i]);
		i++;
	}
	if (str[i] == cc)
		return (&str[i]);
	else
		return (NULL);
}

char	*read_line(int fd, char *stash)
{
	t_Index	index;
	char	*buffer;

	if (!stash)
		stash = ft_gnl_calloc(1, sizeof(char));
	buffer = ft_gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	index.readed = 1;
	while (index.readed > 0 && (ft_gnl_strchr(stash, '\n') == NULL))
	{
		index.readed = read(fd, buffer, BUFFER_SIZE);
		if (index.readed < 0)
		{
			free(buffer);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[index.readed] = '\0';
		stash = ft_gnl_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}
