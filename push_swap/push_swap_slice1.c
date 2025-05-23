/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_slice1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:12:03 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:31:10 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_sma(t_stk *a, t_res *res)
{
	int	i;
	int	j;
	int	k;

	if (a->len < 2)
		return ;
	if (a->len == 2)
	{
		if (a->rank[0] > a->rank[1])
			res->place += sa(a, 1, res);
		return ;
	}
	i = a->rank[0];
	j = a->rank[1];
	k = a->rank[2];
	if (i > j && i > k)
		res->place += ra(a, 1, res);
	else if (j > i && j > k)
		res->place += rra(a, 1, res);
	if (a->rank[0] > a->rank[1])
		res->place += sa(a, 1, res);
}

static void	sort_smb(t_stk *b, t_res *res)
{
	int	i;
	int	j;
	int	k;

	if (b->len < 2)
		return ;
	if (b->len == 2)
	{
		if (b->rank[0] < b->rank[1])
			res->place += sb(b, 1, res);
		return ;
	}
	i = b->rank[0];
	j = b->rank[1];
	k = b->rank[2];
	if (i < j && i < k)
		res->place += rb(b, 1, res);
	else if (j < i && j < k)
		res->place += rrb(b, 1, res);
	if (b->rank[0] < b->rank[1])
		res->place += sb(b, 1, res);
}

static void	mini_slice_help(t_stk *a, t_stk *b, int i, t_res *res)
{
	int	j;

	j = 0;
	while (j < a->len && a->rank[j] != i)
		j++;
	if (j <= a->len / 2)
	{
		while (j > 0)
		{
			res->place += ra(a, 1, res);
			j--;
		}
	}
	else
	{
		j = a->len - j;
		while (j > 0)
		{
			res->place += rra(a, 1, res);
			j--;
		}
	}
	res->place += pb(a, b, res);
}

static void	mini_slice(t_stk *a, t_stk *b, int size, t_res *res)
{
	int	i;

	if (size <= 3)
	{
		sort_sma(a, res);
		return ;
	}
	i = 0;
	while (i < size - 3)
	{
		mini_slice_help(a, b, i, res);
		i++;
	}
	sort_sma(a, res);
	sort_smb(b, res);
	while (b->len > 0)
		res->place += pa(a, b, res);
}

void	slice_sort(t_stk *a, t_stk *b, t_res *res)
{
	int		sort_size;
	t_cnk	cnk;

	sort_size = res->max - res->min + 1;
	if (sort_size <= 6)
	{
		mini_slice(a, b, sort_size, res);
		return ;
	}
	else if (sort_size <= 100)
		cnk.size = 25;
	else if (sort_size <= 500)
		cnk.size = 50;
	else
		return ;
	cnk.num = (sort_size + cnk.size - 1) / cnk.size;
	sort_a_to_b(a, b, &cnk, res);
	sort_b_to_a(a, b, sort_size, res);
}
