/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:24 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:03:32 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_BONUS_H
# define GRAPHICS_BONUS_H

typedef struct s_renderer	t_renderer;
typedef	struct s_floor		t_floor;
typedef struct s_texture	t_texture;
typedef struct s_ray		t_ray;
typedef struct s_engine		t_engine;
typedef struct s_character	t_character;
typedef struct s_world		t_world;

struct			s_renderer
{
	void		*image_ptr;
	char		*image_data;
	int			image_width;
	int			image_height;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	double		*z_buffer;
	t_texture	**sprite_textures;
	int			sprite_text_count;
	t_texture	*textures[4];
	t_texture	*floor_texture;
	t_texture	*ceiling_texture;
	t_texture	*door_texture;
};

typedef struct	s_spr_calc
{
	double		transform_x;
    double		transform_y;
    int			screen_x;
    int			height;
    int			width;
    int			draw_start_y;
    int			draw_end_y;
    int			draw_start_x;
    int			draw_end_x;
}				t_spr_calc;

struct			s_floor
{
    float		ray_dir_x0;
    float		ray_dir_y0;
    float		ray_dir_x1;
    float		ray_dir_y1;
    float		row_dist;
    float		step_x;
    float		step_y;
    float		floor_x;
    float		floor_y;
    int			tx;
    int			ty;
};

void			render_minimap(t_engine *engine);
t_renderer		*renderer_create(void *mlx_ptr);
void			renderer_destroy(t_renderer *renderer, void *mlx_ptr);
void			renderer_clear_screen(t_renderer *renderer, int color);
void			renderer_put_pixel(t_renderer *renderer, int x, int y,
					int color);
int				renderer_get_pixel_color(t_texture *texture, int x, int y);
void			renderer_draw_to_window(t_renderer *renderer, void *mlx_ptr,
					void *win_ptr);

void			render_frame(t_engine *engine);
void			render_walls(t_engine *engine);
void			render_floor_ceiling(t_engine *engine);
void			render_vertical_line(t_renderer *renderer, int x, t_ray *ray,
					t_texture *texture);

void			ray_trace_init(t_ray *ray, t_character *character,
					int screen_x);
void			ray_trace_calculate_step_and_side_dist(t_ray *ray,
					t_character *character);
void			ray_trace_perform_dda(t_ray *ray, t_world *world);
void			ray_trace_calculate_wall_distance(t_ray *ray,
					t_character *character);
void			ray_trace_calculate_draw_limits(t_ray *ray);
void			ray_trace_calculate_wall_x(t_ray *ray, t_character *character);
int				ray_trace_get_texture_index(t_ray *ray);

int				load_all_textures(t_renderer *renderer, t_world *world,
					void *mlx_ptr);
int				load_bonus_textures(t_engine *engine);
void			render_sprites(t_engine *engine);
#endif
