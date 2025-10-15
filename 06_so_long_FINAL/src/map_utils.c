/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prior_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:00:55 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/10 13:00:55 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->h)
	{
		j = 0;
		while (j < game->w)
		{
			ft_putchar_fd(game->map[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	check_extension(char *str)
{
	char	*extension;

	extension = ft_strrchr(str, '.');
	if (extension && ft_strncmp(extension, ".ber", 4) != 0)
		ft_error("Wrong map extension", NULL);
	else if (ft_strlen(extension) != ft_strlen(".ber"))
		ft_error("Wrong map extension", NULL);
}

void	get_dimensions(char *str, t_game *game)
{
	int		i;

	game->h = 0;
	game->w = 0;
	i = 0;
	while (str[i])
	{
		if (game->h == 0 && str[i] != '\n')
			game->w++;
		if (str[i] == '\n')
			game->h++;
		i++;
	}
	if (i > 0 && str[i - 1] != '\n')
		game->h++;
}

void	count_collectibles(t_game *game)
{
	int	y;
	int	x;

	game->collect = 0;
	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == K_TOKEN)
				game->collect++;
			x++;
		}
		y++;
	}
}

void	find_player_pos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == K_PLAYER)
			{
				game->x = x;
				game->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
