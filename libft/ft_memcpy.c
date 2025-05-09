/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:35:36 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:32:39 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char			src[] = "Libft test!";
// 	char			dest[20];
// 	unsigned char	data[] = {1, 2, 3, 4, 5};
// 	unsigned char	copy[5];
// 	char			*null_test;

// 	ft_memcpy(dest, src, 12);
// 	printf("Result after ft_memcpy: %s\n", dest); // → "Libft test!"
// 	// バイナリコピー例
// 	ft_memcpy(copy, data, 5);
// 	printf("Binary copy result:");
// 	for (int i = 0; i < 5; i++)
// 		printf(" %d", copy[i]);
// 	printf("\n");
// 	// NULLチェック（未定義動作を避けるため追加）
// 	null_test = ft_memcpy(NULL, NULL, 0);
// 	if (null_test == NULL)
// 		printf("NULL copy safely returned NULL\n");
// 	return (0);
// }
