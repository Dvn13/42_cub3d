#ifndef CONTROLLER_H
# define CONTROLLER_H

/* Input state structure */
typedef struct s_input
{
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	int		key_esc;
}	t_input;

/* Controller functions */

/* Game controller functions */
int			game_init(t_game *game, char *map_file);
int			game_loop(t_game *game);
void		game_update(t_game *game);
void		game_shutdown(t_game *game);

/* Input handling functions */
int			handle_keypress(int keycode, t_game *game);
int			handle_keyrelease(int keycode, t_game *game);
int			handle_window_close(t_game *game);
void		process_input(t_game *game);

/* Movement controller functions */
void		move_player_forward(t_player *player, t_map *map);
void		move_player_backward(t_player *player, t_map *map);
void		move_player_left(t_player *player, t_map *map);
void		move_player_right(t_player *player, t_map *map);
void		rotate_player_left(t_player *player);
void		rotate_player_right(t_player *player);
int			check_wall_collision(t_player *player, t_map *map, 
				double new_x, double new_y);

/* Event handling functions */
int			main_loop_hook(t_game *game);
void		setup_hooks(t_game *game);

/* Mouse handling functions */
void		mouse_init(void);
void		mouse_toggle(void);
int			mouse_is_enabled(void);
int			handle_mouse_move(int x, int y, t_game *game);
int			handle_mouse_click(int button, int x, int y, t_game *game);

/* Smooth movement functions */
void		smooth_movement_init(void);
void		smooth_movement_update(t_player *player, t_map *map, int keys_pressed[7]);

#endif