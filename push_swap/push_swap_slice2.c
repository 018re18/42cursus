/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:16:31 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 13:22:08 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_cost(int len, int i, int *tmp)
{
	if (i <= len - i)
	{
		*tmp = 0;
		return (i);
	}
	else
	{
		*tmp = 1;
		return (len - i);
	}
}

static void	search_cnk_num(t_stk *a, t_cnk *cnk, t_atb *m)
{
	int	i;
	int	cost;
	int	best;
	int	tmp;

	best = a->len + 1;
	m->idx = -1;
	m->u_or_d = 0;
	i = 0;
	while (i < a->len)
	{
		if (cnk->min <= a->rank[i] && a->rank[i] <= cnk->max)
		{
			cost = get_cost(a->len, i, &tmp);
			if (cost < best)
			{
				best = cost;
				m->idx = i;
				m->u_or_d = tmp;
			}
		}
		i++;
	}
}

static void	mv_a_to_b(t_stk *a, t_stk *b, t_cnk *cnk, t_res *res)
{
	t_atb	m;

	m.count = 0;
	while (m.count < cnk->size)
	{
		search_cnk_num(a, cnk, &m);
		if (m.idx < 0)
			return ;
		if (m.u_or_d == 0)
			m.time = m.idx;
		else
			m.time = a->len - m.idx;
		while (m.time > 0)
		{
			if (m.u_or_d == 0)
				res->place += ra(a, 1, res);
			else
				res->place += rra(a, 1, res);
			m.time--;
		}
		res->place += pb(a, b, res);
		m.count++;
		if (b->rank[0] < (cnk->min + cnk->max) / 2)
			res->place += rb(b, 1, res);
	}
}

void	sort_a_to_b(t_stk *a, t_stk *b, t_cnk *cnk, t_res *res)
{
	int	n_cnk;

	n_cnk = 0;
	while (n_cnk < cnk->num)
	{
		cnk->min = cnk->size * n_cnk;
		cnk->max = cnk->size * (n_cnk + 1) - 1;
		mv_a_to_b(a, b, cnk, res);
		n_cnk++;
	}
}
