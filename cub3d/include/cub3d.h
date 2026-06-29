/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/29 15:16:01 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 1024
# define WIN_H 768
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.06
# define BUFFER_SIZE 4096

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_config
{
	char		**textures;
	int			floor_color;
	int			ceil_color;
	int			floor_set;
	int			ceil_set;
	char		**map;
	int			map_w;
	int			map_h;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
}				t_config;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	double		distance;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			texture;
}				t_ray;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		tex[4];
	t_config	cfg;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}				t_app;

int				parse_cub(const char *path, t_config *cfg);
int				parse_element(t_config *cfg, char *line);
int				copy_and_validate_map(t_config *cfg, char **lines, int count);
int				validate_map(t_config *cfg);
void			free_config(t_config *cfg);
char			*read_scene(const char *path);
char			**split_lines(char *text, int *count);
int				is_map_line(char *line);
int				load_textures(t_app *app);
void			destroy_textures(t_app *app);
int				render_frame(t_app *app);
void			draw_column(t_app *app, int x);
void			update_player(t_app *app);
int				key_press(int keycode, t_app *app);
int				key_release(int keycode, t_app *app);
int				close_window(t_app *app);
void			destroy_app(t_app *app);
void			error_message(char *message);
void			put_pixel(t_img *img, int x, int y, int color);
unsigned int	get_tex_pixel(t_img *tex, int x, int y);
int				color_from_rgb(int r, int g, int b);
int				ft_strlen(char *str);
int				ft_isspace(char c);
int				ft_isdigit(char c);
int				ft_streq(char *a, char *b);
char			*ft_strdup(char *str);
void			ft_bzero(void *ptr, int size);

#endif
