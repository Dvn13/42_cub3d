/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:18:34 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 19:18:35 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_texture	*texture_allocate(void)
{
	t_texture	*texture;

	texture = safe_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->image_ptr = NULL;
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bits_per_pixel = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (texture);
}

int	texture_load_from_file(t_texture *texture, void *mlx_ptr, char *path)
{
	if (!texture || !mlx_ptr || !path)
		return (0);
	texture->image_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->image_ptr)
		return (0);
	texture->data = mlx_get_data_addr(texture->image_ptr,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->data)
	{
		mlx_destroy_image(mlx_ptr, texture->image_ptr);
		texture->image_ptr = NULL;
		return (0);
	}
	return (1);
}

void	texture_destroy(t_texture *texture, void *mlx_ptr)
{
	if (!texture)
		return ;
	if (texture->image_ptr)
		mlx_destroy_image(mlx_ptr, texture->image_ptr);
	safe_free(texture);
}

int	load_all_textures(t_renderer *renderer, t_world *world, void *mlx_ptr)
{
	if (!renderer || !world || !mlx_ptr)
		return (0);
	renderer->textures[0] = texture_allocate();
	if (!renderer->textures[0] || !texture_load_from_file(renderer->textures[0],
			mlx_ptr, world->north_texture_path))
		return (0);
	renderer->textures[1] = texture_allocate();
	if (!renderer->textures[1] || !texture_load_from_file(renderer->textures[1],
			mlx_ptr, world->south_texture_path))
		return (0);
	renderer->textures[2] = texture_allocate();
	if (!renderer->textures[2] || !texture_load_from_file(renderer->textures[2],
			mlx_ptr, world->east_texture_path))
		return (0);
	renderer->textures[3] = texture_allocate();
	if (!renderer->textures[3] || !texture_load_from_file(renderer->textures[3],
			mlx_ptr, world->west_texture_path))
		return (0);
	return (1);
}
