/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:48:11 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:31:17 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*d1;
	const unsigned char	*d2;

	d1 = (const unsigned char *)s1;
	d2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (d1[i] != d2[i])
		{
			return (d1[i] - d2[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*a;
// 	char	*b;
// 	char	x[] = {0, 1, 2, 3, 4};
// 	char	y[] = {0, 1, 2, 3, 5};

// 	a = "abcdef";
// 	b = "abcdeg";
// 	printf("memcmp(a, b, 5) = %d\n", ft_memcmp(a, b, 5)); // → 0
// 	printf("memcmp(a, b, 6) = %d\n", ft_memcmp(a, b, 6)); // → < 0
// 	printf("memcmp(x, y, 5) = %d\n", ft_memcmp(x, y, 5)); // → < 0
// 	printf("memcmp(x, y, 4) = %d\n", ft_memcmp(x, y, 4)); // → 0
// 	return (0);
// }
