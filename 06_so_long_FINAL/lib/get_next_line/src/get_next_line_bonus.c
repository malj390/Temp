/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:58:49 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/06/09 17:16:54 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_line(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = extract_line(stash[fd]);
	if (!line)
		return (ft_free(stash[fd]));
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
