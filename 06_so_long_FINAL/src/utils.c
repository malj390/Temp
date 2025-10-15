/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:47 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/15 20:25:21 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *message, t_game *game)
{
	if (game != NULL)
	{
		delete_images(game);
		delete_textures(game);
		free_map(game->copy_map, game);
		free_map(game->map, game);
		game->copy_map = NULL;
		game->map = NULL;
		if (game->init_mlx)
			mlx_terminate(game->init_mlx);
	}
	if (message != NULL)
		ft_printf(STDERR_FILENO, "Error: %s\n", message);
	exit(1);
}

void	free_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	if (!map || !*map)
		return ;
	while (i < game->h)
	{
		free(map[i]);
		i++;
	}
	free(map);
	game->copy_map = NULL;
}

void	calculate_window_size(t_game *game)
{
	int	ww;
	int	wh;

	game->window_w = game->w * TILESIZE;
	game->window_h = game->h * TILESIZE;
	ww = game->window_w;
	wh = game->window_h;
	if (game->window_w > SCREEN_W)
	{
		ft_printf(STDERR_FILENO, "Map (%d) > Screen (%d)\n", ww, SCREEN_W);
		ft_error("Map width exceeds screen width", game);
	}
	if (game->window_h > SCREEN_H)
	{
		ft_printf(STDERR_FILENO, "Map (%d) > Screen (%d)\n", wh, SCREEN_H);
		ft_error("Map height exceeds screen height", game);
	}
}

void	play_game(t_game *game)
{
	game->init_mlx = mlx_init(game->window_w, game->window_h, "so_long", false);
	if (!game->init_mlx)
		ft_error("Open window", game);
	load_textures(game);
	load_image(game);
	load_image_window(game);
	mlx_key_hook(game->init_mlx, &key_press, game);
	mlx_loop(game->init_mlx);
	game_completed(game);
}
