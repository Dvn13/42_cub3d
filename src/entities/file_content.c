/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:26:43 by gbodur            #+#    #+#             */
/*   Updated: 2026/01/02 18:27:58 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*append_buffer(char *content, char *buffer, int bytes)
{
	char	*temp;

	buffer[bytes] = '\0';
	temp = join_strings(content, buffer);
	safe_free(content);
	return (temp);
}

char	*read_file_content(const char *filename)
{
	int		fd;
	char	*content;
	int		bytes;
	char	buf[1024];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (report_error(strerror(errno)), NULL);
	content = duplicate_string("");
	if (!content)
		return (close(fd), NULL);
	bytes = read(fd, buf, 1023);
	while (bytes > 0)
	{
		content = append_buffer(content, buf, bytes);
		if (!content)
			return (close(fd), NULL);
		bytes = read(fd, buf, 1023);
	}
	close(fd);
	return (content);
}
