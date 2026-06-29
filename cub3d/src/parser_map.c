/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;
	int	content;

	i = 0;
	content = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			content = 1;
		i++;
	}
	return (content);
}

static int	copy_map(t_config *cfg, char **lines, int count)
{
	int	i;
	int	width;

	cfg->map = malloc(count * sizeof(char *));
	if (!cfg->map)
		return (0);
	ft_bzero(cfg->map, count * sizeof(char *));
	cfg->map_h = count;
	i = -1;
	while (++i < count)
	{
		if (!is_map_line(lines[i]))
			return (0);
		cfg->map[i] = ft_strdup(lines[i]);
		if (!cfg->map[i])
			return (0);
		width = ft_strlen(lines[i]);
		if (width > cfg->map_w)
			cfg->map_w = width;
	}
	return (1);
}

int	copy_and_validate_map(t_config *cfg, char **lines, int count)
{
	if (count < 3 || !copy_map(cfg, lines, count) || cfg->map_w < 3)
		return (0);
	return (validate_map(cfg));
}
