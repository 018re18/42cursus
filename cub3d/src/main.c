/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_frame(t_app *app)
{
	app->frame.img = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->frame.img)
		return (0);
	app->frame.addr = mlx_get_data_addr(app->frame.img,
			&app->frame.bits_per_pixel, &app->frame.line_length,
			&app->frame.endian);
	app->frame.width = WIN_W;
	app->frame.height = WIN_H;
	return (app->frame.addr != NULL);
}

static int	init_graphics(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (0);
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, "cub3D");
	if (!app->win)
		return (0);
	if (!create_frame(app) || !load_textures(app))
		return (0);
	return (1);
}

static void	set_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_press, app);
	mlx_hook(app->win, 3, 1L << 1, key_release, app);
	mlx_hook(app->win, 17, 0, close_window, app);
	mlx_loop_hook(app->mlx, render_frame, app);
}

int	main(int argc, char **argv)
{
	t_app	app;

	ft_bzero(&app, sizeof(app));
	if (argc != 2)
		return (error_message("Usage: ./cub3D map.cub"), 1);
	if (!parse_cub(argv[1], &app.cfg))
		return (error_message("Invalid scene description"), 1);
	if (!init_graphics(&app))
	{
		error_message("Failed to initialize graphics or textures");
		destroy_app(&app);
		return (1);
	}
	set_hooks(&app);
	render_frame(&app);
	mlx_loop(app.mlx);
	close_window(&app);
	return (0);
}
