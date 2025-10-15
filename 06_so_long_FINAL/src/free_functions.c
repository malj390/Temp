/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:13:06 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/15 16:24:08 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < ASSET_COUNT)
	{
		mlx_delete_texture(game->assets.tex[i]);
		i++;
	}
}

void	free_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < ASSET_COUNT)
	{
		mlx_delete_image(game->init_mlx, game->assets.img[i]);
		i++;
	}
}

void	delete_textures(t_game *game)
{
	if (game->assets.tex[BG])
		mlx_delete_texture(game->assets.tex[BG]);
	if (game->assets.tex[WALL])
		mlx_delete_texture(game->assets.tex[WALL]);
	if (game->assets.tex[EXIT_C])
		mlx_delete_texture(game->assets.tex[EXIT_C]);
	if (game->assets.tex[EXIT_O])
		mlx_delete_texture(game->assets.tex[EXIT_O]);
	if (game->assets.tex[TOKEN])
		mlx_delete_texture(game->assets.tex[TOKEN]);
	if (game->assets.tex[PLAYER])
		mlx_delete_texture(game->assets.tex[PLAYER]);
}

void	delete_images(t_game *game)
{
	if (game->assets.img[BG])
		mlx_delete_image(game->init_mlx, game->assets.img[BG]);
	if (game->assets.img[WALL])
		mlx_delete_image(game->init_mlx, game->assets.img[WALL]);
	if (game->assets.img[EXIT_C])
		mlx_delete_image(game->init_mlx, game->assets.img[EXIT_C]);
	if (game->assets.img[EXIT_O])
		mlx_delete_image(game->init_mlx, game->assets.img[EXIT_O]);
	if (game->assets.img[TOKEN])
		mlx_delete_image(game->init_mlx, game->assets.img[TOKEN]);
	if (game->assets.img[PLAYER])
		mlx_delete_image(game->init_mlx, game->assets.img[PLAYER]);
}
