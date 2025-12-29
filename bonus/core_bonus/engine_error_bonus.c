/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:05:26 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/29 14:41:25 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	error_handler(char *message, int error_code)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (message)
		write(STDERR_FILENO, message, string_length(message));
	write(STDERR_FILENO, "\n", 1);
	exit(error_code);
}

int		report_error(char *message)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (message)
		write(STDERR_FILENO, message, string_length(message));
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

void	cleanup_engine(t_engine *engine)
{
	int	i;

	if (!engine)
		return ;
	if (engine->world)
	{
		world_destroy(engine->world);
		engine->world = NULL;
	}
	if (engine->renderer && engine->mlx_ptr)
	{
		i = 0;
		while (i < 4)
		{
			if (engine->renderer->textures[i])
				texture_destroy(engine->renderer->textures[i], engine->mlx_ptr);
			i++;
		}
		renderer_destroy(engine->renderer, engine->mlx_ptr);
	}
	if (engine->character)
		character_destroy(engine->character);
	if (engine->win_ptr && engine->mlx_ptr)
		mlx_destroy_window(engine->mlx_ptr, engine->win_ptr);
	if (engine->mlx_ptr)
	{
		mlx_destroy_display(engine->mlx_ptr);
		free(engine->mlx_ptr);
	}
	safe_free(engine);
}
 