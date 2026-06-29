/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(t_config *cfg, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= cfg->map_h || map_x < 0)
		return (0);
	if (map_x >= ft_strlen(cfg->map[map_y]))
		return (0);
	return (cfg->map[map_y][map_x] == '0');
}

static void	move_player(t_config *cfg, double x, double y)
{
	if (is_walkable(cfg, cfg->posx + x, cfg->posy))
		cfg->posx += x;
	if (is_walkable(cfg, cfg->posx, cfg->posy + y))
		cfg->posy += y;
}

static void	rotate_player(t_config *cfg, double speed)
{
	double	old_dir;
	double	old_plane;

	old_dir = cfg->dirx;
	cfg->dirx = cfg->dirx * cos(speed) - cfg->diry * sin(speed);
	cfg->diry = old_dir * sin(speed) + cfg->diry * cos(speed);
	old_plane = cfg->planex;
	cfg->planex = cfg->planex * cos(speed) - cfg->planey * sin(speed);
	cfg->planey = old_plane * sin(speed) + cfg->planey * cos(speed);
}

void	update_player(t_app *app)
{
	if (app->key_w)
		move_player(&app->cfg, app->cfg.dirx * MOVE_SPEED,
			app->cfg.diry * MOVE_SPEED);
	if (app->key_s)
		move_player(&app->cfg, -app->cfg.dirx * MOVE_SPEED,
			-app->cfg.diry * MOVE_SPEED);
	if (app->key_a)
		move_player(&app->cfg, app->cfg.diry * MOVE_SPEED,
			-app->cfg.dirx * MOVE_SPEED);
	if (app->key_d)
		move_player(&app->cfg, -app->cfg.diry * MOVE_SPEED,
			app->cfg.dirx * MOVE_SPEED);
	if (app->key_left)
		rotate_player(&app->cfg, -ROT_SPEED);
	if (app->key_right)
		rotate_player(&app->cfg, ROT_SPEED);
}
