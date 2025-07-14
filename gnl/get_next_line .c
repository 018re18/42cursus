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

//配列strのplaceの位置からlenぶん切り出して返す
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

//numが0の時、配列strから改行までを切りでして返す
//numが0以外の時、改行以降の残り部分を返す
char	*return_line(char *str, int num)
{
	t_line	ln;

	if (!str || str[0] == '\0')
		return (NULL);
	ln.line_len = ft_muluti_func_strlen(str, stop_n);
	ln.str_len = ft_muluti_func_strlen(str, str_len);
	if (ln.line_len == 0 && num == 0)
		return (NULL);
	if (num == 0)
		ln.line = get_line(str, 0, ln.line_len);
	else
	{
		if (ln.str_len <= ln.line_len)
			return (NULL);
		ln.line = get_line(str, ln.line_len, ln.str_len - ln.line_len);
	}
	return (ln.line);
}

//static変数で保持されている文字列をセットして初期化などする
static int	check_save(int fd, t_gnl *gnl, char **save_l)
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

//fdのファイルから改行orEOFまでの文字列を返す
static char	*get_str(int fd, char *str)
{
	int		remain;
	char	*rd_1;

	while (!str || !ft_muluti_func_strlen(str, check_n))
	{
		rd_1 = read_1time(fd, &remain);
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

//呼び出されるたびにfdのファイルから1行を返す
char	*get_next_line(int fd)
{
	t_gnl		gnl;
	static char	*save_l;

	if (!check_save(fd, &gnl, &save_l))
		return (NULL);
	gnl.str = get_str(fd, gnl.str);
	if (!gnl.str || gnl.str[0] == '\0')
	{
		free(gnl.str);
		return (NULL);
	}
	gnl.line = return_line(gnl.str, 0);
	gnl.tmp = return_line(gnl.str, 1);
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
//このmainだとsample.txtのファイルにある文を全て抽出できる