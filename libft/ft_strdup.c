/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:11:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 14:42:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	cpy = (char *)malloc(sizeof(char) * (i + 1));
	if (!(cpy))
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*original;
// 	char	*duplicate;

// 	original = "Hello, 42Tokyo!";
// 	duplicate = ft_strdup(original);
// 	if (duplicate)
// 	{
// 		printf("Original : %s\n", original);
// 		printf("Duplicate: %s\n", duplicate);
// 		free(duplicate);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed\n");
// 	}
// 	return (0);
// }
