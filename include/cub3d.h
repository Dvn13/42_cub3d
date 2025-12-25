/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:30:55 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/25 19:13:34 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "core.h"
# include "entities.h"
# include "graphics.h"
# include "input.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define WINDOW_TITLE "cub3D - 3D"

# define CELL_SIZE 64
# define FIELD_OF_VIEW 66
# define MAX_RENDER_DISTANCE 1000
# define MOVEMENT_VELOCITY 0.05
# define ROTATION_VELOCITY 0.03
# define COLLISION_BUFFER 0.2

# define WALL_SYMBOL '1'
# define FLOOR_SYMBOL '0'
# define NORTH_SPAWN 'N'
# define SOUTH_SPAWN 'S'
# define EAST_SPAWN 'E'
# define WEST_SPAWN 'W'

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307

# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080

# define ERR_MEMORY_ALLOC 1
# define ERR_FILE_ACCESS 2
# define ERR_INVALID_MAP 3
# define ERR_MLX_INIT 4
# define ERR_TEXTURE_LOAD 5

typedef struct s_engine		t_engine;
typedef struct s_character	t_character;
typedef struct s_world		t_world;
typedef struct s_renderer	t_renderer;
typedef struct s_texture	t_texture;
typedef struct s_ray		t_ray;

struct						s_engine
{
	t_world					*world;
	t_character				*character;
	t_renderer				*renderer;
	void					*mlx_ptr;
	void					*win_ptr;
	int						is_running;
	int						key_w;
	int						key_a;
	int						key_s;
	int						key_d;
	int						key_left;
	int						key_right;
	int						mouse_enabled;
};

void						error_handler(char *message, int error_code);
void						cleanup_engine(t_engine *engine);
char						*duplicate_string(const char *s);
int							string_length(const char *s);
int							compare_strings(const char *s1, const char *s2);
char						**split_string(char const *s, char c);
void						free_string_array(char **array);
char						*join_strings(char const *s1, char const *s2);
void						string_copy(char *dest, const char *src, int n);

#endif
