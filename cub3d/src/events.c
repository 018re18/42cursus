/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(int keycode, t_app *app, int value)
{
	if (keycode == 'w' || keycode == 13)
		app->key_w = value;
	if (keycode == 'a' || keycode == 0)
		app->key_a = value;
	if (keycode == 's' || keycode == 1)
		app->key_s = value;
	if (keycode == 'd' || keycode == 2)
		app->key_d = value;
	if (keycode == 65361 || keycode == 123)
		app->key_left = value;
	if (keycode == 65363 || keycode == 124)
		app->key_right = value;
}

int	key_press(int keycode, t_app *app)
{
	if (keycode == 65307 || keycode == 53)
		close_window(app);
	set_key(keycode, app, 1);
	return (0);
}

int	key_release(int keycode, t_app *app)
{
	set_key(keycode, app, 0);
	return (0);
}

int	close_window(t_app *app)
{
	destroy_app(app);
	exit(0);
	return (0);
}
