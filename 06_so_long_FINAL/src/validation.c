/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:35:42 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/10 17:35:42 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map(t_game *game)
{
	validate_borders(game);
	check_rectangularity(game);
	character_validation(game);
	min_characters_validation(game);
}

void	validate_borders(t_game *game)
{
	int	i;
	int	wrong;

	i = 0;
	wrong = 0;
	while (i < game->h)
	{
		if (game->map[i][0] != '1' || game->map[i][game->w - 1] != '1')
			wrong = 1;
		i++;
	}
	i = 0;
	while (i < game->w)
	{
		if (game->map[0][i] != '1' || game->map[game->h - 1][i] != '1')
			wrong = 1;
		i++;
	}
	if (wrong)
		ft_error("Invalid borders", game);
}

void	check_rectangularity(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->h)
	{
		if (ft_strlen(game->map[y]) != (size_t)game->w)
			ft_error("Wrong number of columns in map", game);
		y++;
	}
}

void	character_validation(t_game *game)
{
	char	*valid_chars;
	int		x;
	int		y;
	int		wrong;

	valid_chars = "01PCE";
	x = 0;
	wrong = 0;
	while (x < game->w)
	{
		y = 0;
		while (y < game->h)
		{
			if (ft_strchr(valid_chars, game->map[y][x]) == NULL)
				wrong = 1;
			y++;
		}
		x++;
	}
	if (wrong)
		ft_error("Invalid characters used in map", game);
}

void	min_characters_validation(t_game *game)
{
	int	y;
	int	x;

	game->t_tokens = 0;
	game->t_player = 0;
	game->t_exit = 0;
	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == K_TOKEN)
				game->t_tokens++;
			if (game->map[y][x] == K_PLAYER)
				game->t_player++;
			if (game->map[y][x] == K_EXIT)
				game->t_exit++;
			x++;
		}
		y++;
	}
	if (game->t_tokens < 1 || game->t_player != 1 || game->t_exit != 1)
		ft_error("Wrong min characters", game);
}
