/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:12:03 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 21:10:11 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_cost(int len, int i, int *u_or_d)
{
	if (i <= len - i)
	{
		*u_or_d = 0;
		return (i);
	}
	else
	{
		*u_or_d = 1;
		return (len - i);
	}
}
static void	search_cnk_num(t_stk *A, t_cnk *cnk, t_AtB *m)
{
	int	i;
	int	cost;
	int	best;

	best = A->len + 1;
	m->idx = -1;
	m->u_or_d = 0;
	i = 0;
	while (i < A->len)
	{
		if (cnk->min <= A->rank[i] && A->rank[i] <= cnk->max)
		{
			cost = get_cost(A->len, i, &m->u_or_d);
			if (cost < best)
			{
				best = cost;
				m->idx = i;
			}
		}
		i++;
	}
}

static void	mv_A_to_B(t_stk *A, t_stk *B, t_cnk *cnk, t_res *res)
{
	t_AtB	m;

	m.count = 0;
	while (m.count < cnk->size)
	{
		search_cnk_num(A, cnk, &m);
		if (m.idx < 0)
			return ;
		if (m.u_or_d == 0)
			m.time = m.idx;
		else
			m.time = A->len - m.idx;
		while (m.time > 0)
		{
			if (m.u_or_d == 0)
				res->place += ra(A, 1, res);
			else
				res->place += rra(A, 1, res);
			m.time--;
		}
		res->place += pb(A, B, res);
		m.count++;
		if (B->rank[0] < (cnk->min + cnk->max) / 2)
			res->place += rb(B, 1, res);
	}
}

static void	sort_A_to_B(t_stk *A, t_stk *B, t_cnk *cnk, t_res *res)
{
	int	n_cnk;

	n_cnk = 0;
	while (n_cnk < cnk->num)
	{
		cnk->min = cnk->size * n_cnk;
		cnk->max = cnk->size * (n_cnk + 1) - 1;
		mv_A_to_B(A, B, cnk, res);
		n_cnk++;
	}
}

static int	search_max_num(t_stk *B, int max)
{
	int	i;
	int	j;

	i = 0;
	j = B->len - 1;
	while (i <= j)
	{
		if (B->rank[i] == max)
			return (1);
		if (B->rank[j] == max)
			return (0);
		i++;
		j--;
	}
	return (-1);
}

static void	check_small(t_stk *B, t_res *res, int u_or_d, int max_num)
{
	if (B->rank[0] != max_num)
	{
		if (u_or_d == 1)
			res->place += rb(B, 1, res);
		else
			res->place += rrb(B, 1, res);
	}
}
static void	sort_B_to_A(t_stk *A, t_stk *B, int num, t_res *res)
{
	int	count;
	int	max_num;
	int	j;
	int	u_or_d;

	max_num = res->max;
	count = 0;
	while (count < num)
	{
		u_or_d = search_max_num(B, max_num);
		if (u_or_d < 0)
			return ;
		j = 0;
		while (j < B->len)
		{
			if (B->rank[0] == max_num)
			{
				res->place += pa(A, B, res);
				count++;
				max_num--;
				break ;
			}
			check_small(B,res,u_or_d,max_num);
			j++;
		}
	}
}

static void	sort_sA(t_stk *A, t_res *res)
{
	int	a;
	int	b;
	int	c;

	if (A->len < 2)
		return ;
	if (A->len == 2)
	{
		if (A->rank[0] > A->rank[1])
			res->place += sa(A, 1, res);
		return ;
	}
	a = A->rank[0];
	b = A->rank[1];
	c = A->rank[2];
	if (a > b && a > c)
		res->place += ra(A, 1, res);
	else if (b > a && b > c)
		res->place += rra(A, 1, res);
	if (A->rank[0] > A->rank[1])
		res->place += sa(A, 1, res);
}

static void	sort_sB(t_stk *B, t_res *res)
{
	int	a;
	int	b;
	int	c;

	if (B->len < 2)
		return ;
	if (B->len == 2)
	{
		if (B->rank[0] < B->rank[1])
			res->place += sb(B, 1, res);
		return ;
	}
	a = B->rank[0];
	b = B->rank[1];
	c = B->rank[2];
	if (a < b && a < c)
		res->place += rb(B, 1, res);
	else if (b < a && b < c)
		res->place += rrb(B, 1, res);
	if (B->rank[0] < B->rank[1])
		res->place += sb(B, 1, res);
}

static void	mini_slice(t_stk *A, t_stk *B, int size, t_res *res)
{
	int	i;
	int	j;
	int	k;

	if (size <= 3)
	{
		sort_sA(A, res);
		return ;
	}
	i = size - 3;
	k = 0;
	while (i > 0)
	{
		j = 0;
		while (j < A->len && A->rank[j] != k)
			j++;
		if (j <= A->len / 2)
		{
			while (j > 0)
			{
				res->place += ra(A, 1, res);
				j--;
			}
		}
		else
		{
			j = A->len - j;
			while (j > 0)
			{
				res->place += rra(A, 1, res);
				j--;
			}
		}
		res->place += pb(A, B, res);
		k++;
		i--;
	}
	sort_sA(A, res);
	sort_sB(B, res);
	while (B->len > 0)
		res->place += pa(A, B, res);
}

void	slice_sort(t_stk *A, t_stk *B, t_res *res)
{
	int		sort_size;
	t_cnk	cnk;

	sort_size = res->max - res->min + 1;
	if (sort_size <= 6)
	{
		mini_slice(A, B, sort_size, res);
		return ;
	}
	else if (sort_size <= 100)
		cnk.size = 25;
	else if (sort_size <= 500)
		cnk.size = 50;
	else
		return ;
	cnk.num = (sort_size + cnk.size - 1) / cnk.size;
	sort_A_to_B(A, B, &cnk, res);
	sort_B_to_A(A, B, sort_size, res);
}
