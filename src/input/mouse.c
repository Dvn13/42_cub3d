/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:57:12 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 17:50:07 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_toggle(t_engine *engine)
{
	if (!engine)
		return ;
	engine->mouse_enabled = !engine->mouse_enabled;
	if (engine->mouse_enabled)
	{
		mlx_mouse_move(engine->mlx_ptr, engine->win_ptr,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		mlx_mouse_hide(engine->mlx_ptr, engine->win_ptr);
	}
	else
	{
		mlx_mouse_show(engine->mlx_ptr, engine->win_ptr);
	}
}

int	handle_mouse_movement(int x, int y, t_engine *engine)
{
	int	delta_x;
	int	center_x;
	int	center_y;

	(void)y;
	if (!engine || !engine->mouse_enabled)
		return (0);
	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	if (delta_x > 0)
	{
		rotate_character_right(engine->character);
	}
	else if (delta_x < 0)
	{
		rotate_character_left(engine->character);
	}
	mlx_mouse_move(engine->mlx_ptr, engine->win_ptr, center_x, center_y);
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_engine *engine)
{
	if (!engine)
		return (0);
	(void)x;
	(void)y;
	if (button == 1)
		mouse_toggle(engine);
	return (0);
}
