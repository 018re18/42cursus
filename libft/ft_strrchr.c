/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:12:37 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 16:19:05 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			j = i;
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	if (j >= 0)
	{
		return ((char *)(s + j));
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	*str = "42TokyoTokyo";
// 	char		*res;

// 	// 最後の 'T' を探す
// 	res = ft_strrchr(str, 'T');
// 	if (res)
// 		printf("Found last 'T' at: %s\n", res);
// 	else
// 		printf("'T' not found\n");
// 	// 文字がないケース
// 	res = ft_strrchr(str, 'z');
// 	if (res)
// 		printf("Unexpected: %s\n", res);
// 	else
// 		printf("'z' not found as expected\n");
// 	// null 終端文字の検索
// 	res = ft_strrchr(str, '\0');
// 	if (res)
// 		printf("Null terminator found at: \"%s\" (should be empty)\n", res);
// 	else
// 		printf("Null terminator not found\n");
// 	return (0);
// }
