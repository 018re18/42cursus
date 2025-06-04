/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:58 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/06 14:28:11 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int n)
{
	unsigned char	c;

	c = (unsigned char)n;
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *s)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	char	s;
	int		count;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr(n / 10);
	}
	s = n % 10 + '0';
	write(1, &s, 1);
	count++;
	return (count);
}

int	ft_putnbr_u(unsigned int n)
{
	char	s;
	int		count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_u(n / 10);
	}
	s = n % 10 + '0';
	write(1, &s, 1);
	count++;
	return (count);
}

int	ft_puthex(unsigned int num, int mode)
{
	char	*hex;
	int		count;

	if (mode == 1)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count += ft_puthex(num / 16, mode);
	write(1, &hex[num % 16], 1);
	count++;
	return (count);
}
