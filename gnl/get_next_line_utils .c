/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:56:20 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/05 19:18:51 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//numが0の時、文字列の長さを返す
//numが1の時、改行までの文字列の長さを返す
//numが2の時、文字列に改行があるかのcheckをする
size_t	ft_muluti_func_strlen(char *s, int num)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (num == check_n)
	{
		while (s[i] != '\0')
		{
			if (s[i] == '\n')
				return (0);
			i++;
		}
		return (1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == '\n' && num == stop_n)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

//mallocで長さ1のバッファを確保して返す
static char	*return_malloc_1size(char *s2)
{
	char	*s1;

	s1 = (char *)malloc(sizeof(char) * 1);
	if (!s1)
	{
		free(s2);
		return (NULL);
	}
	s1[0] = '\0';
	return (s1);
}

//s1とs2をあらかじめ用意したdestにコピーする
static void	str_join_helper(char *dest, char *s1, char *s2, t_join *jn)
{
	size_t	i;

	i = 0;
	while (i < jn->s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < jn->s2_len)
	{
		dest[jn->s1_len + i] = s2[i];
		i++;
	}
	dest[jn->s1_len + jn->s2_len] = '\0';
}

//s1とs2を連結した文字列を返して、s1とs2を解放する
char	*ft_strjoin_free(char *s1, char *s2)
{
	t_join	jn;

	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	if (!s1)
		s1 = return_malloc_1size(s2);
	if (!s1)
		return (NULL);
	jn.s1_len = ft_muluti_func_strlen(s1, str_len);
	jn.s2_len = ft_muluti_func_strlen(s2, str_len);
	jn.str = (char *)malloc(sizeof(char) * (jn.s1_len + jn.s2_len + 1));
	if (!jn.str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	str_join_helper(jn.str, s1, s2, &jn);
	free(s1);
	free(s2);
	return (jn.str);
}

//BUFFER_SIZE分のバイトを受け取ったfdから1回ぶん読み込む
char	*read_1time(int fd, int *remain)
{
	char	*rd1;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		*remain = -1;
		return (NULL);
	}
	rd1 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rd1)
	{
		*remain = -1;
		return (NULL);
	}
	*remain = read(fd, rd1, BUFFER_SIZE);
	if (*remain <= 0)
	{
		free(rd1);
		return (NULL);
	}
	rd1[*remain] = '\0';
	return (rd1);
}
