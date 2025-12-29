/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:57:22 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/29 14:39:28 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_handler("Memory allocation failed", ERR_MEMORY_ALLOC);
	return (ptr);
}

void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		error_handler("Memory allocation failed", ERR_MEMORY_ALLOC);
	i = 0;
	while (i < total_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}
