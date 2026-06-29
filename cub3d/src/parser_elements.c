/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	set_texture(t_config *cfg, char *line, int index)
{
	char	*end;
	char	saved;

	line = skip_spaces(line + 2);
	if (!*line || cfg->textures[index])
		return (0);
	end = line + ft_strlen(line);
	while (end > line && ft_isspace(end[-1]))
		end--;
	saved = *end;
	*end = '\0';
	cfg->textures[index] = ft_strdup(line);
	*end = saved;
	return (cfg->textures[index] != NULL);
}

static int	parse_number(char **line, int *number)
{
	int	value;

	*line = skip_spaces(*line);
	if (!ft_isdigit(**line))
		return (0);
	value = 0;
	while (ft_isdigit(**line))
	{
		if (value > 25 || (value == 25 && **line > '5'))
			return (0);
		value = value * 10 + *(*line)++ - '0';
	}
	*number = value;
	*line = skip_spaces(*line);
	return (1);
}

static int	set_color(char *line, int *color, int *is_set)
{
	int	r;
	int	g;
	int	b;

	if (*is_set || !parse_number(&line, &r) || *line++ != ',')
		return (0);
	if (!parse_number(&line, &g) || *line++ != ',')
		return (0);
	if (!parse_number(&line, &b))
		return (0);
	line = skip_spaces(line);
	if (*line)
		return (0);
	*color = color_from_rgb(r, g, b);
	*is_set = 1;
	return (1);
}

int	parse_element(t_config *cfg, char *line)
{
	line = skip_spaces(line);
	if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		return (set_texture(cfg, line, 0));
	if (line[0] == 'S' && line[1] == 'O' && ft_isspace(line[2]))
		return (set_texture(cfg, line, 1));
	if (line[0] == 'W' && line[1] == 'E' && ft_isspace(line[2]))
		return (set_texture(cfg, line, 2));
	if (line[0] == 'E' && line[1] == 'A' && ft_isspace(line[2]))
		return (set_texture(cfg, line, 3));
	if (line[0] == 'F' && ft_isspace(line[1]))
		return (set_color(line + 1, &cfg->floor_color, &cfg->floor_set));
	if (line[0] == 'C' && ft_isspace(line[1]))
		return (set_color(line + 1, &cfg->ceil_color, &cfg->ceil_set));
	return (0);
}
