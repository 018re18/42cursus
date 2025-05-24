/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_body1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:21:26 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/24 21:26:46 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_lord(t_mlx *m, t_num *n)
{
	mlx_put_image_to_window(m->mlx, m->win, m->lord, n->x * n->w, n->y * n->h);
}

void	put_wall(t_mlx *m, t_num *n)
{
	mlx_put_image_to_window(m->mlx, m->win, m->wall, n->x * n->w, n->y * n->h);
}

void	put_coin(t_mlx *m, t_num *n)
{
	mlx_put_image_to_window(m->mlx, m->win, m->coin, n->x * n->w, n->y * n->h);
}
void	put_exit(t_mlx *m, t_num *n)
{
	mlx_put_image_to_window(m->mlx, m->win, m->exit, n->x * n->w, n->y * n->h);
}

void	put_play(t_mlx *m, t_num *n)
{
	mlx_put_image_to_window(m->mlx, m->win, m->play, n->x * n->w, n->y * n->h);
}

int	put_map(t_mlx *m)
{
	t_num	n;

	m->lord = mlx_xpm_file_to_image(m->mlx, "lord.xpm", &n.w, &n.h);
	m->wall = mlx_xpm_file_to_image(m->mlx, "wall.xpm", &n.w, &n.h);
	m->coin = mlx_xpm_file_to_image(m->mlx, "coin.xpm", &n.w, &n.h);
	m->exit = mlx_xpm_file_to_image(m->mlx, "exit.xpm", &n.w, &n.h);
	m->play = mlx_xpm_file_to_image(m->mlx, "player.xpm", &n.w, &n.h);
	if (!m->lord || !m->wall || !m->coin || !m->exit || !m->play)
		return (0);
	n.y = 0;
	while (m->map[n.y])
	{
		n.x = 0;
		while (m->map[n.y][n.x] != '\n' && m->map[n.y][n.x])
		{
			if (m->map[n.y][n.x] == '0')
				put_lord(m, &n);
			else if (m->map[n.y][n.x] == '1')
				put_wall(m, &n);
			else if (m->map[n.y][n.x] == 'C')
				put_coin(m, &n);
			else if (m->map[n.y][n.x] == 'E')
				put_exit(m, &n);
			else if (m->map[n.y][n.x] == 'P')
				put_play(m, &n);
			else
				return (0);
			n.x++;
		}
		n.y++;
	}
	return (1);
}
