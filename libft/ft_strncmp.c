/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:22:31 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:52:34 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*s1 = "42Tokyo";
// 	const char	*s2 = "42ToKyo";
// 	int			res;

// 	res = ft_strncmp(s1, s2, 4);
// 	printf("ft_strncmp (first 4): %d\n", res);
// 	res = ft_strncmp(s1, s2, 10);
// 	printf("ft_strncmp (first 10): %d\n", res);
// 	// 標準関数との比較
// 	printf("strncmp (first 4): %d\n", strncmp(s1, s2, 4));
// 	printf("strncmp (first 10): %d\n", strncmp(s1, s2, 10));
// 	return (0);
// }
