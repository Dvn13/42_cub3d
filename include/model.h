#ifndef MODEL_H
# define MODEL_H

/* Player data structure */
struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		spawn_direction;
};

/* Map data structure */
struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	int			floor_color;
	int			ceiling_color;
	int			player_count;
};

/* Texture data structure */
struct s_texture
{
	void		*img_ptr;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
};

/* Ray data for raycasting */
struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
};

/* Model functions */

/* Map functions */
t_map		*map_create(void);
int			map_parse_file(t_map *map, const char *filename);
int			map_validate(t_map *map);
void		map_destroy(t_map *map);
int			map_is_wall(t_map *map, int x, int y);
char		map_get_cell(t_map *map, int x, int y);

/* Player functions */
t_player	*player_create(void);
void		player_init_position(t_player *player, t_map *map);
void		player_set_direction(t_player *player, char direction);
void		player_destroy(t_player *player);

/* Texture functions */
t_texture	*texture_create(void);
int			texture_load(t_texture *texture, void *mlx_ptr, char *path);
void		texture_destroy(t_texture *texture, void *mlx_ptr);

#endif