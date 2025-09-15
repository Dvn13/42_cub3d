#ifndef VIEW_H
# define VIEW_H

/* Renderer data structure */
struct s_renderer
{
	void		*img_ptr;
	char		*img_data;
	int			img_width;
	int			img_height;
	int			bpp;
	int			size_line;
	int			endian;
	t_texture	*textures[4];
};

/* View functions */

/* Renderer functions */
t_renderer	*renderer_create(void *mlx_ptr);
void		renderer_destroy(t_renderer *renderer, void *mlx_ptr);
void		renderer_clear_screen(t_renderer *renderer, int color);
void		renderer_put_pixel(t_renderer *renderer, int x, int y, int color);
int			renderer_get_pixel_color(t_texture *texture, int x, int y);
void		renderer_draw_to_window(t_renderer *renderer, void *mlx_ptr, 
				void *win_ptr);

/* Rendering functions */
void		render_frame(t_game *game);
void		render_walls(t_game *game);
void		render_floor_ceiling(t_game *game);
void		render_advanced_floor_ceiling(t_game *game);
void		render_optimized_floor_ceiling(t_game *game);
void		render_vertical_line(t_renderer *renderer, int x, t_ray *ray,
				t_texture *texture);
void		render_minimap(t_game *game);
void		render_fps_display(t_renderer *renderer);
void		draw_line(t_renderer *renderer, int x0, int y0, int x1, int y1, 
				int color);

/* Raycasting functions */
void		raycast_init(t_ray *ray, t_player *player, int screen_x);
void		raycast_calculate_step_and_side_dist(t_ray *ray, t_player *player);
void		raycast_perform_dda(t_ray *ray, t_map *map);
void		raycast_calculate_wall_distance(t_ray *ray, t_player *player);
void		raycast_calculate_draw_limits(t_ray *ray);
int			raycast_get_texture_index(t_ray *ray);

/* Texture functions */
int			load_all_textures(t_renderer *renderer, t_map *map, void *mlx_ptr);
void		calculate_texture_coordinates(t_ray *ray, t_player *player,
				t_texture *texture);

#endif