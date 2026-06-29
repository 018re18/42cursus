/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 00:00:00 by kryutaro          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	return (ft_streq(path + len - 4, ".cub"));
}

static int	all_elements_set(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cfg->textures[i])
			return (0);
		i++;
	}
	return (cfg->floor_set && cfg->ceil_set);
}

static int	line_is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	parse_lines(t_config *cfg, char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count && !is_map_line(lines[i]))
	{
		if (!line_is_empty(lines[i]) && !parse_element(cfg, lines[i]))
			return (0);
		i++;
	}
	if (!all_elements_set(cfg) || i == count)
		return (0);
	return (copy_and_validate_map(cfg, lines + i, count - i));
}

int	parse_cub(const char *path, t_config *cfg)
{
	char	*text;
	char	**lines;
	int		count;
	int		result;

	ft_bzero(cfg, sizeof(*cfg));
	cfg->textures = malloc(4 * sizeof(char *));
	if (!cfg->textures)
		return (0);
	ft_bzero(cfg->textures, 4 * sizeof(char *));
	if (!has_cub_extension((char *)path))
		return (free_config(cfg), 0);
	text = read_scene(path);
	if (!text)
		return (free_config(cfg), 0);
	lines = split_lines(text, &count);
	if (!lines)
		return (free(text), free_config(cfg), 0);
	result = parse_lines(cfg, lines, count);
	free(lines);
	free(text);
	if (!result)
		free_config(cfg);
	return (result);
}
