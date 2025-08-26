/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:21:45 by rookuma           #+#    #+#             */
/*   Updated: 2025/08/26 15:39:16 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		j;
	long	num;

	i = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	j = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			j = -1;
		i++;
	}
	num = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		if (j == 1 && num > 2147483647)
			return (0);
		if (j == -1 && (-num) < (-2147483647 - 1))
			return (0);
		i++;
	}
	return ((int)(num * j));
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("Test 1: \"42\" → %d\n", ft_atoi("42"));
// 	printf("Test 2: \"   -42\" → %d\n", ft_atoi("   -42"));
// 	printf("Test 3: \"   +123\" → %d\n", ft_atoi("   +123"));
// 	printf("Test 4: \"0\" → %d\n", ft_atoi("0"));
// 	printf("Test 5: \"   0042\" → %d\n", ft_atoi("   0042"));
// 	printf("Test 6: \"-2147483648\" → %d\n", ft_atoi("-2147483648"));
// 	printf("Test 7: \"2147483647\" → %d\n", ft_atoi("10000000000000"));
// 	printf("Test 8: \"words42\" → %d\n", ft_atoi("words42"));
// 	printf("Test 9: \"\\t\\n 42abc\" → %d\n", ft_atoi("\t\n 42abc"));
// 	printf("Test10: \"--42\" → %d\n", ft_atoi("--42"));
// 	printf("Test11: \"\" → %d\n", ft_atoi(""));
// 	return (0);
// }
