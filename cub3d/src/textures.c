/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (app->tex[i].img)
			mlx_destroy_image(app->mlx, app->tex[i].img);
		app->tex[i].img = NULL;
		i++;
	}
}

static int	load_texture(t_app *app, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(app->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img || texture->width <= 0 || texture->height <= 0)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length,
			&texture->endian);
	if (!texture->addr)
		return (0);
	return (1);
}

int	load_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_texture(app, &app->tex[i], app->cfg.textures[i]))
		{
			destroy_textures(app);
			return (0);
		}
		i++;
	}
	return (1);
}
