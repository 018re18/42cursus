/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:00:47 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:52:47 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*little))
	{
		return ((char *)big);
	}
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
			{
				return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*big = "Hello 42Tokyo students!";
// 	const char	*little = "42Tokyo";
// 	char		*res;

// 	res = ft_strnstr(big, little, 20);
// 	if (res)
// 		printf("Found: %s\n", res);
// 	else
// 		printf("Not found within length\n");
// 	// 比較: lenが短すぎて見つからない
// 	res = ft_strnstr(big, little, 4);
// 	if (res)
// 		printf("Unexpected: %s\n", res);
// 	else
// 		printf("Correctly not found (len=4)\n");
// 	// 空文字列検索
// 	res = ft_strnstr(big, "", 10);
// 	if (res)
// 		printf("Empty needle returns: %s\n", res);
// 	else
// 		printf("Empty needle not handled correctly\n");
// 	return (0);
// }
