#ifndef INPUT_H
# define INPUT_H

int		handle_key_press(int keycode, t_engine *engine);
int		handle_key_release(int keycode, t_engine *engine);
int		handle_window_close(t_engine *engine);
void	process_input(t_engine *engine);

void	move_character_forward(t_character *character, t_world *world);
void	move_character_backward(t_character *character, t_world *world);
void	move_character_left(t_character *character, t_world *world);
void	move_character_right(t_character *character, t_world *world);
void	rotate_character_left(t_character *character);
void	rotate_character_right(t_character *character);
int		check_wall_collision(t_character *character, t_world *world,
			double new_x, double new_y);

int		main_loop_hook(t_engine *engine);
void	setup_event_hooks(t_engine *engine);

void	mouse_initialize(void);
void	mouse_toggle(void);
int		mouse_is_enabled(void);
int		handle_mouse_movement(int x, int y, t_engine *engine);
int		handle_mouse_click(int button, int x, int y, t_engine *engine);

#endif
