/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:58:49 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 17:54:50 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer)
{
	free(buffer);
	return (NULL);
}

size_t	ft_strlen_char(const char *str, char c)
{
	long	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*update_stash(char *stash)
{
	char	*temp;
	t_Index	index;

	if (!stash)
		return (NULL);
	index.jump = ft_strlen_char(stash, '\n');
	index.total = ft_strlen_char(stash, '\0');
	if (index.jump + 1 >= index.total)
		return (ft_free(stash));
	temp = stash;
	stash = ft_substr(stash + index.jump + 1, 0, index.total - index.jump - 1);
	free(temp);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	t_Index	index;

	if (!stash)
		return (NULL);
	line = NULL;
	index.jump = ft_strlen_char(stash, '\n');
	line = ft_substr(stash, 0, index.jump + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
		return (ft_free(stash));
	stash = update_stash(stash);
	return (line);
}
