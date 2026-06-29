/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	map_at(t_config *cfg, int x, int y)
{
	if (y < 0 || y >= cfg->map_h || x < 0 || x >= ft_strlen(cfg->map[y]))
		return (' ');
	return (cfg->map[y][x]);
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	cell_is_closed(t_config *cfg, int x, int y)
{
	char	c;

	c = map_at(cfg, x, y);
	if (c != '0' && !is_player(c))
		return (1);
	if (map_at(cfg, x - 1, y) == ' ' || map_at(cfg, x + 1, y) == ' ')
		return (0);
	if (map_at(cfg, x, y - 1) == ' ' || map_at(cfg, x, y + 1) == ' ')
		return (0);
	return (1);
}

static void	set_player(t_config *cfg, int x, int y, char direction)
{
	cfg->posx = x + 0.5;
	cfg->posy = y + 0.5;
	cfg->dirx = (direction == 'E') - (direction == 'W');
	cfg->diry = (direction == 'S') - (direction == 'N');
	cfg->planex = -cfg->diry * 0.66;
	cfg->planey = cfg->dirx * 0.66;
	cfg->map[y][x] = '0';
}

int	validate_map(t_config *cfg)
{
	int		x;
	int		y;
	int		players;
	char	c;

	players = 0;
	y = -1;
	while (++y < cfg->map_h)
	{
		x = -1;
		while (++x < ft_strlen(cfg->map[y]))
		{
			c = cfg->map[y][x];
			if (c != ' ' && c != '0' && c != '1' && !is_player(c))
				return (0);
			if (!cell_is_closed(cfg, x, y))
				return (0);
			if (is_player(c) && ++players == 1)
				set_player(cfg, x, y, c);
		}
	}
	return (players == 1);
}
