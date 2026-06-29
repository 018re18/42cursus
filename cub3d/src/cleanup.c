/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *cfg)
{
	int	i;

	i = 0;
	while (cfg->textures && i < 4)
		free(cfg->textures[i++]);
	free(cfg->textures);
	i = 0;
	while (cfg->map && i < cfg->map_h)
		free(cfg->map[i++]);
	free(cfg->map);
	ft_bzero(cfg, sizeof(*cfg));
}

void	destroy_app(t_app *app)
{
	if (app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
	destroy_textures(app);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	free_config(&app->cfg);
}
