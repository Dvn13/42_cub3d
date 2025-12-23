/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:57:12 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 13:57:13 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	g_mouse_enabled = 0;
static int	g_last_mouse_x = 0;

void	mouse_initialize(void)
{
	g_mouse_enabled = 0;
	g_last_mouse_x = SCREEN_WIDTH / 2;
}

void	mouse_toggle(void)
{
	g_mouse_enabled = !g_mouse_enabled;
}

int	mouse_is_enabled(void)
{
	return (g_mouse_enabled);
}

int	handle_mouse_movement(int x, int y, t_engine *engine)
{
	int	delta_x;

	if (!engine || !engine->character || !g_mouse_enabled)
		return (0);
	(void)y;
	delta_x = x - g_last_mouse_x;
	if (delta_x > 0)
	{
		rotate_character_right(engine->character);
	}
	else if (delta_x < 0)
	{
		rotate_character_left(engine->character);
	}
	g_last_mouse_x = x;
	return (0);
}

int	handle_mouse_click(int button, int x, int y, t_engine *engine)
{
	if (!engine)
		return (0);
	(void)x;
	(void)y;
	if (button == 1)
	{
		mouse_toggle();
		if (g_mouse_enabled)
		{
			g_last_mouse_x = SCREEN_WIDTH / 2;
//			mlx_mouse_hide();
		}
		else
		{
//			mlx_mouse_show();
		}
	}
	return (0);
}
