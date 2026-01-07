/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:19:27 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/07 16:34:56 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_BONUS_H
# define INPUT_BONUS_H

typedef struct s_engine		t_engine;
typedef struct s_character	t_character;
typedef struct s_world		t_world;

int		check_wall_collision(t_character *character, t_world *world,
			double new_x, double new_y);

void	setup_event_hooks(t_engine *engine);

int		handle_key_press(int keycode, t_engine *engine);
int		handle_key_release(int keycode, t_engine *engine);
int		handle_window_close(t_engine *engine);

void	mouse_toggle(t_engine *engine);
int		handle_mouse_movement(int x, int y, t_engine *engine);
int		handle_mouse_click(int button, int x, int y, t_engine *engine);

void	move_character_forward(t_character *character, t_world *world);
void	move_character_backward(t_character *character, t_world *world);
void	move_character_left(t_character *character, t_world *world);
void	move_character_right(t_character *character, t_world *world);

void	process_input(t_engine *engine);
void	check_sprite_collection(t_engine *engine);

void	rotate_character_right(t_character *character);
void	rotate_character_left(t_character *character);

#endif
