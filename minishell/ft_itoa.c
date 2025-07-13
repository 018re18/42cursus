/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryutaro <kryutaro@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:27:41 by kryutaro          #+#    #+#             */
/*   Updated: 2025/06/30 18:46:08 by kryutaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_digits(int n)
{
	int		count;
	long	num;

	count = 0;
	num = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count = 1;
		num = -num;
	}
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	convert_number(long num, char *result, int len)
{
	if (num == 0)
		result[0] = '0';
	result[len] = '\0';
	while (num > 0)
	{
		result[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	num;
	int		sign;

	sign = 0;
	len = count_digits(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	num = n;
	if (n < 0)
	{
		sign = 1;
		result[0] = '-';
		num = -num;
	}
	convert_number(num, result, len);
	return (result);
}
// #include <stdio.h>

// int	main(void)
// {
// 	int	n;

// 	n = 199990;
// 	printf("%s", ft_itoa(n));
// }
