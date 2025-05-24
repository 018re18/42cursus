/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:56:49 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/24 20:44:37 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_mlx	m;

	m.map = get_map("sample.ber");
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, 1000, 1000, "so_long");
	if (!put_map(&m))
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	mlx_loop(m.mlx);
	return (0);
}
