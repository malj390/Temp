/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:16 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/13 13:58:34 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_exit(t_game *game)
{
	ft_printf(1, "All tokens collected! Exit is now open.\n");
	iii_mitw(game, EXIT_O, game->x_exit, game->y_exit);
}

void	check_move(t_game *game, int y, int x, int direction)
{
	if (game->map[y][x] != K_WALL)
	{
		if (game->map[y][x] == K_TOKEN)
		{
			game->t_tokens--;
			game->map[y][x] = K_BG;
			if (iii_mitw(game, BG, x, y))
				ft_error("Load background", game);
			if (game->t_tokens == 0)
				update_exit(game);
		}
		if (game->map[y][x] != K_EXIT)
			move_player(game, direction);
		if (game->map[y][x] == K_EXIT && game->t_tokens == 0)
			game_completed(game);
		reload_player(game, direction);
	}
}

void	move_player(t_game *game, int direction)
{
	mlx_image_t	*img_player;

	img_player = game->assets.img[PLAYER];
	if (direction == UP)
	{
		game->y--;
		img_player->instances[0].y -= TILESIZE;
	}
	else if (direction == DOWN)
	{
		game->y++;
		img_player->instances[0].y += TILESIZE;
	}
	else if (direction == LEFT)
	{
		game->x--;
		img_player->instances[0].x -= TILESIZE;
	}
	else if (direction == RIGHT)
	{
		game->x++;
		img_player->instances[0].x += TILESIZE;
	}
	game->move++;
	ft_printf(1, "Moves: %d\n", game->move);
}

const char	*player_path_for_dir(int direction)
{
	if (direction == UP)
		return (PLAYER_U_PATH);
	if (direction == DOWN)
		return (PLAYER_D_PATH);
	if (direction == LEFT)
		return (PLAYER_L_PATH);
	if (direction == RIGHT)
		return (PLAYER_R_PATH);
	return (PLAYERPATH);
}

void	reload_player(t_game *game, int direction)
{
	mlx_delete_image(game->init_mlx, game->assets.img[PLAYER]);
	game->assets.tex[PLAYER] = mlx_load_png(player_path_for_dir(direction));
	ii_mtti(game, PLAYER);
	mlx_delete_texture(game->assets.tex[PLAYER]);
	if (!game->assets.img[PLAYER])
		ft_error("Error load image_player", game);
	mlx_image_to_window(game->init_mlx,
		game->assets.img[PLAYER], game->x * TILESIZE, game->y * TILESIZE);
}
