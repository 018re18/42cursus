/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:37:42 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 12:52:36 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_r(int *res)
{
	int	i;
	int	j;

	i = 0;
	while (res[i])
	{
		if (res[i] == 3 && res[i + 1] == 4 || res[i] == 4 && res[i + 1] == 3)
		{
			res[i] = 5;
			i++;
			j = i;
			while (res[j])
			{
				res[j] = res[j + 1];
				j++;
			}
			res[j] = 0;
		}
		else if (res[i] == 6 && res[i + 1] == 7 || res[i] == 7 && res[i
			+ 1] == 6)
		{
			res[i] = 8;
			i++;
			j = i;
			while (res[j])
			{
				res[j] = res[j + 1];
				j++;
			}
			res[j] = 0;
		}
		else
			i++;
	}
}

void	put_res(int *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i] == 1)
			write(1, "pa\n", 3);
		else if (res[i] == 2)
			write(1, "pb\n", 3);
		else if (res[i] == 3)
			write(1, "ra\n", 3);
		else if (res[i] == 4)
			write(1, "rb\n", 3);
		else if (res[i] == 5)
			write(1, "rr\n", 3);
		else if (res[i] == 6)
			write(1, "rra\n", 4);
		else if (res[i] == 7)
			write(1, "rrb\n", 4);
		else if (res[i] == 8)
			write(1, "rrr\n", 4);
		else if (res[i] == 9)
			write(1, "sa\n", 3);
		else if (res[i] == 10)
			write(1, "sb\n", 3);
		i++;
	}
}
