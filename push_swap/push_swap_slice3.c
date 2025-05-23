/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:19:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:37:10 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	search_max_num(t_stk *b, int max)
{
	int	i;
	int	j;

	i = 0;
	j = b->len - 1;
	while (i <= j)
	{
		if (b->rank[i] == max)
			return (1);
		if (b->rank[j] == max)
			return (0);
		i++;
		j--;
	}
	return (-1);
}

static void	check_small(t_stk *b, t_res *res, int u_or_d, int max_num)
{
	if (b->rank[0] != max_num)
	{
		if (u_or_d == 1)
			res->place += rb(b, 1, res);
		else
			res->place += rrb(b, 1, res);
	}
}

void	sort_b_to_a(t_stk *a, t_stk *b, int num, t_res *res)
{
	t_bta	m;

	m.max_num = res->max;
	m.count = 0;
	while (m.count < num)
	{
		m.u_or_d = search_max_num(b, m.max_num);
		if (m.u_or_d < 0)
			return ;
		m.j = 0;
		while (m.j < b->len)
		{
			if (b->rank[0] == m.max_num)
			{
				res->place += pa(a, b, res);
				m.count++;
				m.max_num--;
				break ;
			}
			check_small(b, res, m.u_or_d, m.max_num);
			m.j++;
		}
	}
}
