/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:12:04 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/05 22:29:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*str = "libft is cool!";
// 	char		*res;

// 	res = ft_strchr(str, 'i');
// 	if (res)
// 		printf("Found: %s\n", res);
// 	else
// 		printf("Character not found\n");
// 	res = ft_strchr(str, 'z');
// 	if (res)
// 		printf("Found: %s\n", res);
// 	else
// 		printf("Character not found\n");
// 	res = ft_strchr(str, '\0');
// 	if (res)
// 		printf("Found null terminator at: \"%s\"\n", res);
// 	else
// 		printf("Null terminator not found\n");
// 	return (0);
// }
