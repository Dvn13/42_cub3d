/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:21 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/08 19:20:36 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_BONUS_H
# define ENTITIES_BONUS_H

typedef struct s_position	t_position;
typedef struct s_direction	t_direction;
typedef struct s_character	t_character;
typedef struct s_world		t_world;
typedef struct s_texture	t_texture;
typedef struct s_ray		t_ray;
typedef struct s_renderer	t_renderer;

struct						s_position
{
	double					x;
	double					y;
};

struct						s_direction
{
	double					x;
	double					y;
};

struct						s_character
{
	struct s_position		pos;
	struct s_direction		dir;
	struct s_direction		plane;
	char					spawn_orientation;
};

typedef struct s_sprite
{
	double					x;
	double					y;
	int						texture_id;
	int						is_collected;
	double					dist;
}							t_sprite;

struct						s_world
{
	char					**grid;
	int						width;
	int						height;
	char					*north_texture_path;
	char					*south_texture_path;
	char					*east_texture_path;
	char					*west_texture_path;
	char					*floor_texture_path;
	char					*ceiling_texture_path;
	char					*door_texture_path;
	int						floor_color;
	int						ceiling_color;
	int						character_count;
	int						px;
	int						py;
	t_sprite				*sprites;
	int						sprite_count;
	int						current_sprite_frame;
};

struct						s_texture
{
	void					*image_ptr;
	char					*data;
	int						width;
	int						height;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
};

struct						s_ray
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					perp_wall_dist;
	int						step_x;
	int						step_y;
	int						hit;
	int						side;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						texture_index;
	double					wall_x;
	int						texture_x;
};

t_character					*character_allocate(void);
void						character_initialize_position(
								t_character *character,
								t_world *world);
void						character_destroy(t_character *character);

char						*read_file_content(const char *filename);

int							is_map_line(char *line);
void						parse_map_dimensions(char **lines, int start_index,
								t_world *world);
void						copy_map_data(char **lines, int start_index,
								t_world *world);

int							count_map_players(t_world *world);
int 						check_space_map(t_world *world);								
int							validate_map_layout(char *content);

t_texture					*texture_allocate(void);
int							texture_load_from_file(t_texture *texture,
								void *mlx_ptr, char *path);
void						texture_destroy(t_texture *texture, void *mlx_ptr);
int							load_all_textures(t_renderer *renderer,
								t_world *world, void *mlx_ptr);

int							world_validate(t_world *world);
int							world_is_wall(t_world *world, int x, int y);
char						world_get_cell(t_world *world, int x, int y);

t_world						*world_create(void);
void						world_destroy(t_world *world);

int							parse_color_or_texture(t_world *world, char *line);
int							world_parse_file(t_world *world,
								const char *filename);

int							check_floor_ceiling_set(t_world *world);
int							check_textures_loaded(t_world *world);
int							init_sprite_positions(t_world *world);
int							count_map_players(t_world *world);

int							parse_color_value(char *color_str);

int							check_map_closed(t_world *world);

int							parse_texture_line(t_world *world, char *line);

#endif
