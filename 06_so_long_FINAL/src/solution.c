/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:36:35 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/10 17:36:35 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(t_game *game)
{
	char	**copy_map;
	int		i;

	copy_map = (char **)malloc(sizeof(char *) * (game->h + 1));
	if (!copy_map)
		return (NULL);
	i = -1;
	while (++i < game->h)
	{
		copy_map[i] = ft_strdup(game->map[i]);
		if (!copy_map[i])
			ft_error("Failed to allocate memory for map copy", game);
	}
	copy_map[i] = NULL;
	return (copy_map);
}

void	validate_path(t_game *game)
{
	int		start_x;
	int		start_y;
	char	**tmp_map;

	tmp_map = copy_map(game);
	if (!tmp_map)
		ft_error("Failed to copy map for validation", game);
	game->copy_map = tmp_map;
	game->collect = 0;
	game->exit_found = 0;
	start_x = game->x;
	start_y = game->y;
	if (start_y < 0 || start_y >= game->h || start_x < 0 || start_x >= game->w)
		ft_error("Player position out of bounds", game);
	floodfill_recursive(game, start_y, start_x);
	if (!game->exit_found || game->collect != game->t_tokens)
		ft_error("Map is not solvable", game);
	free_map(game->copy_map, game);
	game->copy_map = NULL;
}

void	floodfill_recursive(t_game *game, int y, int x)
{
	char	orig;

	if (!is_valid_position(game, y, x))
		return ;
	orig = game->copy_map[y][x];
	process_tile(game, y, x);
	if (orig == K_EXIT)
		return ;
	floodfill_recursive(game, y, x + 1);
	floodfill_recursive(game, y, x - 1);
	floodfill_recursive(game, y + 1, x);
	floodfill_recursive(game, y - 1, x);
}

int	is_valid_position(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->h)
		return (0);
	if (x < 0 || x >= game->w)
		return (0);
	if (game->copy_map[y][x] == '1')
		return (0);
	if (game->copy_map[y][x] == '*')
		return (0);
	return (1);
}

void	process_tile(t_game *game, int y, int x)
{
	char	original_tile;

	original_tile = game->copy_map[y][x];
	if (original_tile == K_EXIT)
	{
		game->exit_found = 1;
		game->copy_map[y][x] = '*';
		return ;
	}
	if (original_tile == K_TOKEN)
		game->collect++;
	game->copy_map[y][x] = '*';
}
