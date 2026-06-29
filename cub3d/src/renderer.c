/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_app *app)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(&app->frame, x, y, app->cfg.ceil_color);
			else
				put_pixel(&app->frame, x, y, app->cfg.floor_color);
		}
	}
}

int	render_frame(t_app *app)
{
	int	x;

	update_player(app);
	draw_background(app);
	x = -1;
	while (++x < WIN_W)
		draw_column(app, x);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}
