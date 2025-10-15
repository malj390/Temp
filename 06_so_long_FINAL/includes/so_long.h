/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:40:34 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/10/15 15:58:33 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "MLX42.h"
# include <stdlib.h>

# define WIDTH 256
# define HEIGHT 256
# define WALL1PATH "assets/textures/tree.png"
# define BGPATH "assets/textures/bg.png"
# define EXIT_C_PATH "assets/textures/exit_close.png"
# define EXIT_O_PATH "assets/textures/exit_open.png"
# define TOKENPATH "assets/textures/coin.png"
# define PLAYERPATH "assets/textures/player_D1.png"
# define PLAYER_D_PATH "assets/textures/player_D1.png"
# define PLAYER_U_PATH "assets/textures/player_U1.png"
# define PLAYER_L_PATH "assets/textures/player_L1.png"
# define PLAYER_R_PATH "assets/textures/player_R1.png"
# define K_WALL '1'
# define K_EXIT 'E'
# define K_TOKEN 'C'
# define K_PLAYER 'P'
# define K_BG '0'
# define TILESIZE 96
# define KU1 MLX_KEY_UP
# define KD1 MLX_KEY_DOWN
# define KL1 MLX_KEY_LEFT
# define KR1 MLX_KEY_RIGHT
# define KU2 MLX_KEY_W
# define KD2 MLX_KEY_S
# define KL2 MLX_KEY_A
# define KR2 MLX_KEY_D
# define SCREEN_W 3840 // 1920 // 3840 (42)
# define SCREEN_H 2160 // 1080 // 2160 (42)

typedef enum e_print
{
	PRINT,
	NO_PRINT,
	RANDOM,
	SINGLE
}	t_print;

typedef enum player_action
{
	NEUTRAL,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
}	t_player_action;
typedef enum e_asset_type
{
	BG,
	WALL,
	EXIT_C,
	EXIT_O,
	TOKEN,
	PLAYER,
	ASSET_COUNT
}	t_asset_type;

typedef struct s_assets
{
	mlx_texture_t	*tex[ASSET_COUNT];
	mlx_image_t		*img[ASSET_COUNT];
}	t_assets;

typedef struct s_game
{
	int			h;
	int			w;
	int			window_w;
	int			window_h;
	int			t_tokens;
	int			t_player;
	int			t_exit;
	char		**map;
	char		**copy_map;
	int			collect;
	int			exit_found;
	int			x_exit;
	int			y_exit;
	int			x;
	int			y;
	int			move;
	int			init_status;
	mlx_t		*init_mlx;
	t_assets	assets;
}	t_game;

// src/free_functions.c
void	free_textures(t_game *game);
void	free_images(t_game *game);
void	delete_textures(t_game *game);
void	delete_images(t_game *game);

// src/helpers.c
char	*get_texpath(int type);
int		i_mlp(t_game *game, t_asset_type type);
int		iii_mitw(t_game *game, t_asset_type type, int x, int y);
int		ii_mtti(t_game *game, t_asset_type type);

// src/main.c
void	key_press(mlx_key_data_t key, void *game);
void	game_completed(t_game *game);
void	init_game(t_game *game);
int		main(int argc, char **argv);

// src/map_utils.c
void	print_map(t_game *game);
void	check_extension(char *str);
void	get_dimensions(char *str, t_game *game);
void	count_collectibles(t_game *game);
void	find_player_pos(t_game *game);

// src/play_game.c
void	put_image(t_game *game, int y, int x);
void	load_textures(t_game *game);
void	load_image(t_game *game);
void	load_image_window(t_game *game);

// src/player.c
void	update_exit(t_game *game);
void	check_move(t_game *game, int y, int x, int direction);
void	move_player(t_game *game, int direction);
void	reload_player(t_game *game, int direction);

// src/read_map.c
char	*read_file(char *filepath);
void	str_to_array(char *str, t_game *game);
void	read_map(char *filename, t_game *game);
void	map_init_val(t_game *game, char *filename);

// src/solution.c
char	**copy_map(t_game *game);
void	validate_path(t_game *game);
void	floodfill_recursive(t_game *game, int y, int x);
int		is_valid_position(t_game *game, int y, int x);
void	process_tile(t_game *game, int y, int x);

// src/utils.c
void	ft_error(char *message, t_game *game);
void	free_map(char **map, t_game *game);
void	calculate_window_size(t_game *game);
void	play_game(t_game *game);

// src/validation.c
void	validate_map(t_game *game);
void	validate_borders(t_game *game);
void	check_rectangularity(t_game *game);
void	character_validation(t_game *game);
void	min_characters_validation(t_game *game);

#endif