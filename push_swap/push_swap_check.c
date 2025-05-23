/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:37:42 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:47:51 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	shift_op(int *res, int i, int op)
{
	int	j;

	res[i] = op;
	j = i + 1;
	while (res[j])
	{
		res[j] = res[j + 1];
		j++;
	}
}

void	check_rrr(int *r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		if ((r[i] == 3 && r[i + 1] == 4) || (r[i] == 4 && r[i + 1] == 3))
			shift_op(r, i, 5);
		else if ((r[i] == 6 && r[i + 1] == 7) || (r[i] == 7 && r[i + 1] == 6))
			shift_op(r, i, 8);
		i++;
	}
}

static void	check_op(int *res, int i)
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
}

void	put_res(int *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		check_op(res, i);
		i++;
	}
}
