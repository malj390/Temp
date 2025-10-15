/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:32:00 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/10 17:32:00 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_file(char *filepath)
{
	int		fd;
	char	*content;
	char	*line;
	char	*tmp;

	content = NULL;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!content)
			content = ft_strdup(line);
		else
		{
			tmp = ft_strjoin(content, line);
			free(content);
			content = tmp;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

void	str_to_array(char *str, t_game *game)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	x = 0;
	i = 0;
	game->map = malloc(sizeof(char *) * (game->h + 1));
	if (!game->map)
		return ;
	while (y < game->h)
	{
		game->map[y] = malloc(sizeof(char) * (game->w + 1));
		if (!game->map[y])
			return ;
		x = 0;
		while (x < game->w && str[i] && str[i] != '\n')
			game->map[y][x++] = str[i++];
		game->map[y][x] = '\0';
		if (str[i] == '\n')
			i++;
		y++;
	}
	game->map[y] = NULL;
}

void	read_map(char *filename, t_game *game)
{
	char	*buffer;

	check_extension(filename);
	buffer = read_file(filename);
	get_dimensions(buffer, game);
	str_to_array(buffer, game);
	validate_map(game);
	free(buffer);
}

void	map_init_val(t_game *game, char *filename)
{
	game->init_status = 1;
	read_map(filename, game);
	validate_map(game);
	count_collectibles(game);
	find_player_pos(game);
	validate_path(game);
	calculate_window_size(game);
	game->init_status = 0;
}
