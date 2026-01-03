/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:24 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/31 20:48:25 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct s_renderer	t_renderer;
typedef struct s_floor		t_floor;

struct						s_renderer
{
	void					*image_ptr;
	char					*image_data;
	int						image_width;
	int						image_height;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	t_texture				*textures[4];
	t_texture				*floor_texture;
	t_texture				*ceiling_texture;
};

void						render_minimap(t_engine *engine);
t_renderer					*renderer_create(void *mlx_ptr);
void						renderer_destroy(t_renderer *renderer,
								void *mlx_ptr);
void						renderer_clear_screen(t_renderer *renderer,
								int color);
void						renderer_put_pixel(t_renderer *renderer, int x,
								int y, int color);
int							renderer_get_pixel_color(t_texture *texture, int x,
								int y);
void						renderer_draw_to_window(t_renderer *renderer,
								void *mlx_ptr, void *win_ptr);

void						render_frame(t_engine *engine);
void						render_walls(t_engine *engine);
void						render_floor_ceiling(t_engine *engine);
void						render_vertical_line(t_renderer *renderer, int x,
								t_ray *ray, t_texture *texture);

void						ray_trace_init(t_ray *ray, t_character *character,
								int screen_x);
void						ray_trace_calculate_step_and_side_dist(t_ray *ray,
								t_character *character);
void						ray_trace_perform_dda(t_ray *ray, t_world *world);
void						ray_trace_calculate_wall_distance(t_ray *ray,
								t_character *character);
void						ray_trace_calculate_draw_limits(t_ray *ray);
void						ray_trace_calculate_wall_x(t_ray *ray,
								t_character *character);
int							ray_trace_get_texture_index(t_ray *ray);

int							load_all_textures(t_renderer *renderer,
								t_world *world, void *mlx_ptr);

#endif
