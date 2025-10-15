/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:24 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/15 22:19:32 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, int y, int x)
{
	iii_mitw(game, BG, x, y);
	if (game->map[y][x] == K_WALL)
		iii_mitw(game, WALL, x, y);
	else if (game->map[y][x] == K_EXIT)
	{
		game->x_exit = x;
		game->y_exit = y;
		iii_mitw(game, EXIT_C, x, y);
	}
	else if (game->map[y][x] == K_PLAYER)
		iii_mitw(game, PLAYER, x, y);
	else if (game->map[y][x] == K_TOKEN)
		iii_mitw(game, TOKEN, x, y);
}

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < ASSET_COUNT)
	{
		game->assets.tex[i] = NULL;
		i_mlp(game, i);
		i++;
	}
}

void	load_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < ASSET_COUNT)
	{
		game->assets.img[i] = NULL;
		ii_mtti(game, i);
		i++;
	}
	delete_textures(game);
}

void	load_image_window(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (game->map[y][x])
		{
			put_image(game, y, x);
			x++;
		}
		y++;
	}
	iii_mitw(game, PLAYER, game->x, game->y);
}
