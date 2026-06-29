/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = img->addr + y * img->line_length;
	pixel += x * (img->bits_per_pixel / 8);
	*(unsigned int *)pixel = color;
}

unsigned int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + y * tex->line_length;
	pixel += x * (tex->bits_per_pixel / 8);
	return (*(unsigned int *)pixel);
}

int	color_from_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	ft_bzero(void *ptr, int size)
{
	unsigned char	*bytes;

	bytes = ptr;
	while (size-- > 0)
		*bytes++ = 0;
}
