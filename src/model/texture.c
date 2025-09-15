#include "cub3d.h"

t_texture	*texture_create(void)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img_ptr = NULL;
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (texture);
}

static int	check_file_extension(char *path)
{
	int	len;
	
	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(&path[len - 4], ".xpm") == 0)
		return (1);
	return (0);
}

int	texture_load(t_texture *texture, void *mlx_ptr, char *path)
{
	int	file_type;

	if (!texture || !mlx_ptr || !path)
		return (0);
	file_type = check_file_extension(path);
	if (file_type == 1)
	{
		texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, 
			&texture->width, &texture->height);
	}
	else
		return (0);
	if (!texture->img_ptr)
		return (0);
	texture->data = mlx_get_data_addr(texture->img_ptr, &texture->bpp, 
		&texture->size_line, &texture->endian);
	if (!texture->data)
	{
		mlx_destroy_image(mlx_ptr, texture->img_ptr);
		texture->img_ptr = NULL;
		return (0);
	}
	return (1);
}

void	texture_destroy(t_texture *texture, void *mlx_ptr)
{
	if (!texture)
		return ;
	if (texture->img_ptr && mlx_ptr)
		mlx_destroy_image(mlx_ptr, texture->img_ptr);
	free(texture);
}