/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:38:00 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:51:42 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (d_len >= size)
	{
		return (size + s_len);
	}
	i = d_len;
	j = 0;
	while ((i + j + 1) < size && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (d_len + s_len);
}

// #include <stdio.h>
// #include <string.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	main(void)
// {
// 	char		buffer[20] = "Hello";
// 	const char	*src = " World!";
// 	size_t		dstsize;
// 	size_t		ret;
// 	char		std_buffer[20] = "Hello";
// 	size_t		std_ret;

// 	dstsize = sizeof(buffer);
// 	ret = ft_strlcat(buffer, src, dstsize);
// 	printf("Result: %s\n", buffer);
// 	printf("Return value: %zu\n", ret);
// 	// 標準関数との比較
// 	std_ret = strlcat(std_buffer, src, dstsize);
// 	printf("Standard strlcat: %s\n", std_buffer);
// 	printf("Standard return: %zu\n", std_ret);
// 	return (0);
// }
