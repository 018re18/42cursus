/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*append_buffer(char *text, int size, char *buffer, int read_size)
{
	char	*joined;
	int		i;

	joined = malloc((size + read_size + 1) * sizeof(char));
	if (!joined)
		return (free(text), NULL);
	i = -1;
	while (++i < size)
		joined[i] = text[i];
	i = -1;
	while (++i < read_size)
		joined[size + i] = buffer[i];
	joined[size + read_size] = '\0';
	free(text);
	return (joined);
}

char	*read_scene(const char *path)
{
	char	buffer[BUFFER_SIZE];
	char	*text;
	int		fd;
	int		size;
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	text = NULL;
	size = 0;
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		text = append_buffer(text, size, buffer, bytes);
		if (!text)
			return (close(fd), NULL);
		size += bytes;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	if (bytes < 0 || !text)
		return (free(text), NULL);
	return (text);
}

static int	count_lines(char *text)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (text[i])
	{
		if (text[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && text[i - 1] == '\n')
		count--;
	return (count);
}

char	**split_lines(char *text, int *count)
{
	char	**lines;
	int		i;
	int		line;

	*count = count_lines(text);
	lines = malloc(*count * sizeof(char *));
	if (!lines)
		return (NULL);
	lines[0] = text;
	i = 0;
	line = 1;
	while (text[i])
	{
		if (text[i] == '\r')
			text[i] = '\0';
		if (text[i] == '\n')
		{
			text[i] = '\0';
			if (line < *count)
				lines[line++] = text + i + 1;
		}
		i++;
	}
	return (lines);
}
