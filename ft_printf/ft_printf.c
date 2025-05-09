/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:16:24 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/09 16:43:27 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_conv(char conv, va_list arg)
{
	if (conv == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (conv == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (conv == 'p')
		return (ft_putpoi(va_arg(arg, void *)));
	else if (conv == 'd' || conv == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	else if (conv == 'u')
		return (ft_putnbr_u(va_arg(arg, unsigned int)));
	else if (conv == 'x')
		return (ft_puthex(va_arg(arg, unsigned int), 0));
	else if (conv == 'X')
		return (ft_puthex(va_arg(arg, unsigned int), 1));
	else if (conv == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *conv, ...)
{
	va_list	arg;
	int		i;
	int		count;

	va_start(arg, conv);
	i = 0;
	count = 0;
	while (conv[i] != '\0')
	{
		if (conv[i] == '%' && conv[i + 1])
		{
			count += ft_check_conv(conv[i + 1], arg);
			i++;
		}
		else
		{
			write(1, &conv[i], 1);
			count++;
		}
		i++;
	}
	va_end(arg);
	return (count);
}

// #include "ft_printf.h"
// #include <stdio.h>

// int	main(void)
// {
// 	int		ret_std;
// 	int		ret_ft;
// 	void	*ptr;

// 	// 文字
// 	ret_std = printf("%");
// 	ret_ft = ft_printf("%");
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 文字列
// 	ret_std = printf("2. std: String: %s\n", "42Tokyo");
// 	ret_ft = ft_printf("2.  ft: String: %s\n", "42Tokyo");
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// NULL文字列
// 	ret_std = printf("3. std: Null: %s\n", (char *)NULL);
// 	ret_ft = ft_printf("3.  ft: Null: %s\n", (char *)NULL);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 整数
// 	ret_std = printf("4. std: Number: %d\n", 667476941976296722974);
// 	ret_ft = ft_printf("4.  ft: Number: %d\n",984984578783212222123);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 符号なし整数
// 	ret_std = printf("5. std: Unsigned: %u\n", 4294967295U);
// 	ret_ft = ft_printf("5.  ft: Unsigned: %u\n", 4294967295U);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 小文字16進数
// 	ret_std = printf("6. std: Hex lower: %x\n", 305441741);
// 	ret_ft = ft_printf("6.  ft: Hex lower: %x\n", 305441741);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 大文字16進数
// }
// 	#include "ft_printf.h"
// #include <stdio.h>

// int	main(void)
// {
// 	int		ret_std;
// 	int		ret_ft;
// 	void	*ptr;

	// // 文字
	// ret_std = printf("%");
	// ret_ft = ft_printf("%");
	// printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
	// // 文字列
	// ret_std = printf("2. std: String: %s\n", "42Tokyo");
	// ret_ft = ft_printf("2.  ft: String: %s\n", "42Tokyo");
	// printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
	// // NULL文字列
	// ret_std = printf("3. std: Null: %s\n", (char *)NULL);
	// ret_ft = ft_printf("3.  ft: Null: %s\n", (char *)NULL);
	// printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
	// // 整数
	// ret_std = printf("4. std: Number: %d\n", 2147483648);
	// ret_ft = ft_printf("4.  ft: Number: %d\n", 2147483648);
	// printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 符号なし整数
// 	ret_std = printf("5. std: Unsigned: %u\n", 4294967295U);
// 	ret_ft = ft_printf("5.  ft: Unsigned: %u\n", 4294967295U);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 小文字16進数
// 	ret_std = printf("6. std: Hex lower: %x\n", 305441741);
// 	ret_ft = ft_printf("6.  ft: Hex lower: %x\n", 305441741);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// 大文字16進数
// 	ret_std = printf("7. std: Hex upper: %X\n", 305441741);
// 	ret_ft = ft_printf("7.  ft: Hex upper: %X\n", 305441741);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// ポインタ
// 	ptr = (void *)0x1234abcd;
// 	ret_std = printf("8. std: Pointer: %p\n", ptr);
// 	ret_ft = ft_printf("8.  ft: Pointer: %p\n", ptr);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// NULLポインタ
// 	ret_std = printf("9. std: Null pointer: %p\n", NULL);
// 	ret_ft = ft_printf("9.  ft: Null pointer: %p\n", NULL);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// パーセント
// 	ret_std = printf("10. std: Percent: %%\n");
// 	ret_ft = ft_printf("10.  ft: Percent: %%\n");
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	return (0);
// }ret_std = printf("8. std: Pointer: %p\n", ptr);
// 	ret_ft = ft_printf("8.  ft: Pointer: %p\n", ptr);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// NULLポインタ
// 	ret_std = printf("9. std: Null pointer: %p\n", NULL);
// 	ret_ft = ft_printf("9.  ft: Null pointer: %p\n", NULL);
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	// パーセント
// 	ret_std = printf("10. std: Percent: %%\n");
// 	ret_ft = ft_printf("10.  ft: Percent: %%\n");
// 	printf("ret_std = %d, ret_ft = %d\n\n", ret_std, ret_ft);
// 	return (0);
// }
