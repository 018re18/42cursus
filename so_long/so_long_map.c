/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:22:09 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/24 21:14:36 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

int	count_line(char *name)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		free(line);
		count++;
	}
	close(fd);
	return (count);
}
char	**get_map(char *name)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;
	int		line_num;

	line_num = count_line(name);
	if (line_num <= 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (line_num + 1));
	if (!map)
		return (NULL);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
