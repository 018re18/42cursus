/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_app *app, t_ray *ray, int x)
{
	double	camera_x;

	ft_bzero(ray, sizeof(*ray));
	camera_x = 2.0 * x / WIN_W - 1.0;
	ray->dir_x = app->cfg.dirx + app->cfg.planex * camera_x;
	ray->dir_y = app->cfg.diry + app->cfg.planey * camera_x;
	ray->map_x = (int)app->cfg.posx;
	ray->map_y = (int)app->cfg.posy;
	ray->delta_x = 1e30;
	ray->delta_y = 1e30;
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y != 0)
		ray->delta_y = fabs(1.0 / ray->dir_y);
	ray->step_x = 1;
	ray->step_y = 1;
	if (ray->dir_x < 0)
		ray->step_x = -1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
}

static void	cast_ray(t_app *app, t_ray *ray)
{
	ray->side_x = (ray->map_x + 1.0 - app->cfg.posx) * ray->delta_x;
	ray->side_y = (ray->map_y + 1.0 - app->cfg.posy) * ray->delta_y;
	if (ray->step_x < 0)
		ray->side_x = (app->cfg.posx - ray->map_x) * ray->delta_x;
	if (ray->step_y < 0)
		ray->side_y = (app->cfg.posy - ray->map_y) * ray->delta_y;
	while (app->cfg.map[ray->map_y][ray->map_x] != '1')
	{
		ray->side = (ray->side_y <= ray->side_x);
		if (ray->side == 0)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
		}
	}
}

static void	set_wall(t_app *app, t_ray *ray)
{
	if (ray->side == 0)
		ray->distance = ray->side_x - ray->delta_x;
	else
		ray->distance = ray->side_y - ray->delta_y;
	ray->line_h = (int)(WIN_H / ray->distance);
	if (ray->line_h < 1)
		ray->line_h = 1;
	ray->draw_start = -ray->line_h / 2 + WIN_H / 2;
	ray->draw_end = ray->line_h / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = app->cfg.posy + ray->distance * ray->dir_y;
	else
		ray->wall_x = app->cfg.posx + ray->distance * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static int	texture_x(t_app *app, t_ray *ray)
{
	int	x;

	if (ray->side == 0 && ray->dir_x > 0)
		ray->texture = 2;
	else if (ray->side == 0)
		ray->texture = 3;
	else if (ray->dir_y > 0)
		ray->texture = 0;
	else
		ray->texture = 1;
	x = (int)(ray->wall_x * app->tex[ray->texture].width);
	if (ray->side == 0 && ray->dir_x > 0)
		x = app->tex[ray->texture].width - x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		x = app->tex[ray->texture].width - x - 1;
	return (x);
}

void	draw_column(t_app *app, int x)
{
	t_ray			ray;
	double			step;
	double			position;
	unsigned int	color;
	int				tex_x;

	init_ray(app, &ray, x);
	cast_ray(app, &ray);
	set_wall(app, &ray);
	tex_x = texture_x(app, &ray);
	step = (double)app->tex[ray.texture].height / ray.line_h;
	position = (ray.draw_start - WIN_H / 2.0 + ray.line_h / 2.0) * step;
	while (ray.draw_start <= ray.draw_end)
	{
		color = get_tex_pixel(&app->tex[ray.texture], tex_x, (int)position);
		if (ray.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(&app->frame, x, ray.draw_start++, color);
		position += step;
	}
}
