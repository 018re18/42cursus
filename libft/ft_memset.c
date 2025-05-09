/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:37:36 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:36:37 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*f;

	f = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		f[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char			str[20] = "Hello, World!";
// 	unsigned char	buffer[10];

// 	printf("Before: %s\n", str);
// 	ft_memset(str + 7, '*', 5);
// 	printf("After : %s\n", str); // → Hello, *****d!
// 	// バイナリ配列をゼロ埋め
// 	ft_memset(buffer, 0xAB, 10);
// 	printf("Buffer filled with 0xAB:");
// 	for (int i = 0; i < 10; i++)
// 		printf(" %02X", buffer[i]);
// 	printf("\n");
// 	// NULLチェック（len = 0 のとき）
// 	if (ft_memset(NULL, 'x', 0) == NULL)
// 		printf("NULL with len=0 is safely handled.\n");
// 	return (0);
// }
