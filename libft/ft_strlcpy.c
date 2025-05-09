/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:26:30 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:51:31 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	if (size == 0)
	{
		return (j);
	}
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
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
// 	char		dst[10];
// 	const char	*src = "42Tokyo";
// 	size_t		ret;
// 	char		std_dst[10];
// 	size_t		std_ret;

// 	ret = ft_strlcpy(dst, src, sizeof(dst));
// 	printf("Copied: %s\n", dst);
// 	printf("Return value: %zu\n", ret);
// 	// 標準関数との比較
// 	std_ret = strlcpy(std_dst, src, sizeof(std_dst));
// 	printf("Standard strlcpy: %s\n", std_dst);
// 	printf("Standard return: %zu\n", std_ret);
// 	return (0);
// }
