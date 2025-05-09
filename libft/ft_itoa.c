/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:24 by rookuma           #+#    #+#             */
/*   Updated: 2025/04/30 17:03:41 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long nb)
{
	int	len;

	len = 1;
	while (nb / 10)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		j;
	int		len;
	char	*num;
	long	nb;

	nb = (long)n;
	j = 0;
	if (nb < 0)
	{
		j = 1;
		nb = -nb;
	}
	len = count(nb);
	num = (char *)malloc(sizeof(char) * (len + j + 1));
	if (!num)
		return (NULL);
	num[len + j] = '\0';
	while (len-- > 0)
	{
		num[len + j] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (j == 1)
		num[0] = '-';
	return (num);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*res;

// 	res = ft_itoa(0);
// 	printf("ft_itoa(0) = %s\n", res);
// 	free(res);
// 	res = ft_itoa(42);
// 	printf("ft_itoa(42) = %s\n", res);
// 	free(res);
// 	res = ft_itoa(-42);
// 	printf("ft_itoa(-42) = %s\n", res);
// 	free(res);
// 	res = ft_itoa(2147483647);
// 	printf("ft_itoa(2147483647) = %s\n", res);
// 	free(res);
// 	res = ft_itoa(-2147483648);
// 	printf("ft_itoa(-2147483648) = %s\n", res);
// 	free(res);
// 	res = ft_itoa(1000000);
// 	printf("ft_itoa(1000000) = %s\n", res);
// 	free(res);
// 	return (0);
// }
