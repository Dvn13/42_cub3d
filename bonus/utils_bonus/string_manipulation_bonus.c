/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:57:31 by gbodur            #+#    #+#             */
/*   Updated: 2025/12/23 13:57:32 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	copy_string_part(char *dest, const char *src, int start, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[start + i] = src[i];
		i++;
	}
}

char	*join_strings(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = string_length(s1);
	len2 = string_length(s2);
	result = safe_malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	copy_string_part(result, s1, 0, len1);
	copy_string_part(result, s2, len1, len2);
	result[len1 + len2] = '\0';
	return (result);
}

void	string_copy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}
