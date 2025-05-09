/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:33:35 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:27:49 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*f;

	f = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (f[i] == (unsigned char)c)
		{
			return ((void *)(f + i));
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char			*data = "Hello, World!";
// 	char				target;
// 	char				*found;
// 	const unsigned char	bin[] = {0x01, 0x02, 0x03, 0x04, 0x05};
// 	unsigned char		*found_bin;

// 	target = 'W';
// 	found = ft_memchr(data, target, strlen(data));
// 	if (found)
// 		printf("Found '%c' at position: %ld\n", target, found - data);
// 	else
// 		printf("Character '%c' not found\n", target);
// 	target = 'z';
// 	found = ft_memchr(data, target, strlen(data));
// 	if (found)
// 		printf("Found '%c' at position: %ld\n", target, found - data);
// 	else
// 		printf("Character '%c' not found\n", target);
// 	found_bin = ft_memchr(bin, 0x03, 5);
// 	if (found_bin)
// 		printf("Found byte 0x03 at offset: %ld\n", found_bin
// 			- (unsigned char *)bin);
// 	else
// 		printf("Byte 0x03 not found\n");
// 	return (0);
// }
