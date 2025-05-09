/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:59:06 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 17:04:08 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_got(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src && n != 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	else
	{
		str_got(d, s, n);
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	buffer[20] = "1234567890";
// 	char	buffer2[20] = "1234567890";
// 	char	*null_test;

// 	printf("Before ft_memmove overlap forward: %s\n", buffer);
// 	ft_memmove(buffer + 2, buffer, 8); // 領域が重なる（前方向にコピー）
// 	printf("After ft_memmove overlap forward:  %s\n", buffer);
// 	printf("Before ft_memmove overlap backward: %s\n", buffer2);
// 	ft_memmove(buffer2, buffer2 + 2, 8); // 領域が重なる（後ろ方向にコピー）
// 	printf("After ft_memmove overlap backward:  %s\n", buffer2);
// 	// NULLチェック（安全な未使用時）
// 	null_test = ft_memmove(NULL, NULL, 0);
// 	if (null_test == NULL)
// 		printf("NULL test passed (returned NULL)\n");
// 	return (0);
// }
