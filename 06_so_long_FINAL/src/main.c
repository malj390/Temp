/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:08 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/15 20:20:55 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_press(mlx_key_data_t key, void *game)
{
	t_game	*aux;

	aux = (t_game *)game;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(aux->init_mlx);
	if ((key.key == KU1 || key.key == KU2) && key.action == MLX_PRESS)
		check_move(aux, aux->y - 1, aux->x, UP);
	if ((key.key == KD1 || key.key == KD2) && key.action == MLX_PRESS)
		check_move(aux, aux->y + 1, aux->x, DOWN);
	if ((key.key == KL1 || key.key == KL2) && key.action == MLX_PRESS)
		check_move(aux, aux->y, aux->x - 1, LEFT);
	if ((key.key == KR1 || key.key == KR2) && key.action == MLX_PRESS)
		check_move(aux, aux->y, aux->x + 1, RIGHT);
}

void	game_completed(t_game *game)
{
	ft_printf(1, "Game finished!!! Well done\n");
	delete_images(game);
	delete_textures(game);
	free_map(game->map, game);
	// mlx_close_window(game->init_mlx);
	//free_map(game->map, game);
	mlx_terminate(game->init_mlx);
	exit(0);
}

void	init_game(t_game *game)
{
	game->h = 0;
	game->w = 0;
	game->t_tokens = 0;
	game->t_player = 0;
	game->t_exit = 0;
	game->x = 0;
	game->y = 0;
	game->x_exit = 0;
	game->y_exit = 0;
	game->move = 0;
	game->init_status = 0;
	return ;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		init_game(&game);
		map_init_val(&game, argv[1]);
		if (game.init_status == 0)
			play_game(&game);
		else
		{
			ft_error(NULL, &game);
			return (1);
		}
	}
	else
		ft_error("Arguments no valid", NULL);
	return (0);
}
