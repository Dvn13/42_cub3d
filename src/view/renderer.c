#include "cub3d.h"

t_renderer	*renderer_create(void *mlx_ptr)
{
	t_renderer	*renderer;
	int			i;

	renderer = ft_calloc(1, sizeof(t_renderer));
	if (!renderer)
		return (NULL);
	renderer->img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!renderer->img_ptr)
	{
		free(renderer);
		return (NULL);
	}
	renderer->img_data = mlx_get_data_addr(renderer->img_ptr, &renderer->bpp,
		&renderer->size_line, &renderer->endian);
	renderer->img_width = WINDOW_WIDTH;
	renderer->img_height = WINDOW_HEIGHT;
	i = 0;
	while (i < 4)
	{
		renderer->textures[i] = NULL;
		i++;
	}
	return (renderer);
}

void	renderer_destroy(t_renderer *renderer, void *mlx_ptr)
{
	int	i;

	if (!renderer)
		return ;
	if (renderer->img_ptr && mlx_ptr)
		mlx_destroy_image(mlx_ptr, renderer->img_ptr);
	i = 0;
	while (i < 4)
	{
		if (renderer->textures[i])
			texture_destroy(renderer->textures[i], mlx_ptr);
		i++;
	}
	free(renderer);
}

void	renderer_clear_screen(t_renderer *renderer, int color)
{
	int	x;
	int	y;

	if (!renderer)
		return ;
	y = 0;
	while (y < renderer->img_height)
	{
		x = 0;
		while (x < renderer->img_width)
		{
			renderer_put_pixel(renderer, x, y, color);
			x++;
		}
		y++;
	}
}

void	renderer_put_pixel(t_renderer *renderer, int x, int y, int color)
{
	char	*pixel;

	if (!renderer || x < 0 || x >= renderer->img_width || 
		y < 0 || y >= renderer->img_height)
		return ;
	pixel = renderer->img_data + (y * renderer->size_line + x * (renderer->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	renderer_draw_to_window(t_renderer *renderer, void *mlx_ptr, void *win_ptr)
{
	if (!renderer || !mlx_ptr || !win_ptr)
		return ;
	mlx_put_image_to_window(mlx_ptr, win_ptr, renderer->img_ptr, 0, 0);
}

int	renderer_get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (!texture || !texture->data || x < 0 || x >= texture->width || 
		y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}