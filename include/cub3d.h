#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# include "../mlx/mlx.h"

/* Window dimensions */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "Cub3D - 3D Maze Explorer"

/* Game constants */
# define TILE_SIZE 64
# define FOV 60
# define MAX_RENDER_DISTANCE 1000
# define MOVEMENT_SPEED 0.05
# define ROTATION_SPEED 0.03

/* Map characters */
# define WALL_CHAR '1'
# define FLOOR_CHAR '0'
# define NORTH_SPAWN 'N'
# define SOUTH_SPAWN 'S'
# define EAST_SPAWN 'E'
# define WEST_SPAWN 'W'

/* Key codes (Linux X11) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* Colors */
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080

/* Error codes */
# define ERR_MALLOC 1
# define ERR_FILE_OPEN 2
# define ERR_INVALID_MAP 3
# define ERR_MLX_INIT 4
# define ERR_TEXTURE_LOAD 5

/* Forward declarations */
typedef struct s_game		t_game;
typedef struct s_player		t_player;
typedef struct s_map		t_map;
typedef struct s_renderer	t_renderer;
typedef struct s_texture	t_texture;
typedef struct s_ray		t_ray;

/* Include MVC components */
# include "model.h"
# include "view.h"
# include "controller.h"

/* Main game structure */
struct s_game
{
	t_map			*map;
	t_player		*player;
	t_renderer		*renderer;
	void			*mlx_ptr;
	void			*win_ptr;
	int				running;
};

/* Utility functions */
void	ft_error(char *message, int error_code);
void	ft_cleanup(t_game *game);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	free_string_array(char **array);
char	*ft_strjoin(char const *s1, char const *s2);

/* Performance monitoring */
void	perf_start_frame(void);
void	perf_end_frame(void);
double	perf_get_current_fps(void);
double	perf_get_average_fps(void);
long	perf_get_frame_count(void);
void	perf_reset_stats(void);

#endif