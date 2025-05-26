/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:16:31 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/26 18:50:00 by rookuma          ###   ########.fr       */
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
	int	off;

	n_cnk = 0;
	off = 0;
	if (cnk->size == 25 && cnk->num == 4)
		cnk->num = 6;
	while (n_cnk < cnk->num)
	{
		if (n_cnk < 2 && cnk->size == 25)
			cnk->size = 25;
		else if (n_cnk < 3 && cnk->size == 25)
			cnk->size = 20;
		else if (n_cnk < 6 && cnk->size == 20)
			cnk->size = 10;
		cnk->min = off;
		cnk->max = off + cnk->size - 1;
		mv_a_to_b(a, b, cnk, res);
		off += cnk->size;
		n_cnk++;
	}
}
