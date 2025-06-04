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

size_t	ft_strlen_c_n(char *s, int num)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (num == 2)
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
		if (s[i] == '\n' && num == 1)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

static char	*rtn_m1(char *s2)
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

static void	str_j(char *dest, char *s1, char *s2, t_join *jn)
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	t_join	jn;

	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	if (!s1)
		s1 = rtn_m1(s2);
	if (!s1)
		return (NULL);
	jn.s1_len = ft_strlen_c_n(s1, 0);
	jn.s2_len = ft_strlen_c_n(s2, 0);
	jn.str = (char *)malloc(sizeof(char) * (jn.s1_len + jn.s2_len + 1));
	if (!jn.str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	str_j(jn.str, s1, s2, &jn);
	free(s1);
	free(s2);
	return (jn.str);
}

char	*rd_1t(int fd, int *remain)
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
