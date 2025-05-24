/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:40:59 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/24 21:27:35 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	**map;
	void	*lord;
	void	*wall;
	void	*coin;
	void	*exit;
	void	*play;
}			t_mlx;

typedef struct s_num
{
	int		x;
	int		y;
	int		w;
	int		h;
}			t_num;

int			put_map(t_mlx *m);
char		**get_map(char *name);

#endif
