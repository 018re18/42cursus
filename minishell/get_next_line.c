/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:55:03 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/28 12:36:35 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str, size_t place, size_t len)
{
	size_t	i;
	char	*line;

	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[place + i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*rtn_line(char *str, int num)
{
	t_line	ln;

	if (!str || str[0] == '\0')
		return (NULL);
	ln.ln_len = ft_strlen_c_n(str, 1);
	ln.str_len = ft_strlen_c_n(str, 0);
	if (ln.ln_len == 0 && num == 0)
		return (NULL);
	if (num == 0)
		ln.line = get_line(str, 0, ln.ln_len);
	else
	{
		if (ln.str_len <= ln.ln_len)
			return (NULL);
		ln.line = get_line(str, ln.ln_len, ln.str_len - ln.ln_len);
	}
	return (ln.line);
}

static int	check(int fd, t_gnl *gnl, char **save_l)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (*save_l)
		{
			free(*save_l);
			*save_l = NULL;
		}
		return (0);
	}
	if (*save_l)
	{
		gnl->str = *save_l;
		*save_l = NULL;
	}
	else
		gnl->str = NULL;
	return (1);
}

static char	*get_str(int fd, char *str)
{
	int		remain;
	char	*rd_1;

	while (!str || ft_strlen_c_n(str, 2))
	{
		rd_1 = rd_1t(fd, &remain);
		if (!rd_1)
		{
			if (remain == -1)
			{
				free(str);
				return (NULL);
			}
			break ;
		}
		str = ft_strjoin_free(str, rd_1);
		if (!str)
		{
			return (NULL);
		}
	}
	return (str);
}

char	*get_next_line(int fd)
{
	t_gnl		gnl;
	static char	*save_l;

	if (!check(fd, &gnl, &save_l))
		return (NULL);
	gnl.str = get_str(fd, gnl.str);
	if (!gnl.str || gnl.str[0] == '\0')
	{
		free(gnl.str);
		return (NULL);
	}
	gnl.line = rtn_line(gnl.str, 0);
	gnl.tmp = rtn_line(gnl.str, 1);
	free(gnl.str);
	if (!gnl.line)
	{
		free(gnl.tmp);
		return (NULL);
	}
	save_l = gnl.tmp;
	return (gnl.line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("sample.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
