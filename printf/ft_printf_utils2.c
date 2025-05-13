/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:27:51 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/06 14:41:27 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_ul(unsigned long num)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count += ft_puthex_ul(num / 16);
	write(1, &hex[num % 16], 1);
	count++;
	return (count);
}

int	ft_putpoi(void *str)
{
	unsigned long	num;
	char			*hex;
	int				count;

	if (!str)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	write(1, "0x", 2);
	count = 2;
	num = (unsigned long)str;
	hex = "0123456789abcdef";
	if (num >= 16)
	{
		count += ft_puthex_ul(num / 16);
	}
	write(1, &hex[num % 16], 1);
	count++;
	return (count);
}
