/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:04:33 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/10 01:04:33 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_texpath(int type)
{
	if (type == TOKEN)
		return (TOKENPATH);
	else if (type == EXIT_C)
		return (EXIT_C_PATH);
	else if (type == EXIT_O)
		return (EXIT_O_PATH);
	else if (type == BG)
		return (BGPATH);
	else if (type == PLAYER)
		return (PLAYERPATH);
	else if (type == WALL)
		return (WALL1PATH);
	return (NULL);
}

int	i_mlp(t_game *game, t_asset_type type)
{
	game->assets.tex[type] = mlx_load_png(get_texpath(type));
	if (!game->assets.tex[type])
	{
		// delete_textures(game);
		ft_error("Load texture failed", game);
		return (-1);
	}
	return (0);
}

int	iii_mitw(t_game *game, t_asset_type type, int x, int y)
{
	int			pos_x;
	int			pos_y;
	mlx_image_t	*img;

	pos_x = x * TILESIZE;
	pos_y = y * TILESIZE;
	img = game->assets.img[type];
	if (!mlx_image_to_window(game->init_mlx, img, pos_x, pos_y))
		return (-1);
	return (0);
}

int	ii_mtti(t_game *game, t_asset_type type)
{
	mlx_texture_t	*tex;

	tex = game->assets.tex[type];
	game->assets.img[type] = mlx_texture_to_image(game->init_mlx, tex);
	if (!game->assets.img[type])
	{
		ft_error("Load image failed", game);
		return (-1);
	}
	return (0);
}
