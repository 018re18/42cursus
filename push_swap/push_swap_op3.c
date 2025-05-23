/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:37:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:35:11 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_stk *a, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (a->len < 2)
		return (0);
	i = a->len - 1;
	tmp = a->stk[i];
	while (i > 0)
	{
		a->stk[i] = a->stk[i - 1];
		i--;
	}
	a->stk[0] = tmp;
	i = a->len - 1;
	tmp = a->rank[i];
	while (i > 0)
	{
		a->rank[i] = a->rank[i - 1];
		i--;
	}
	a->rank[0] = tmp;
	if (mode == 1)
		res->result[res->place] = 6;
	return (1);
}

int	rrb(t_stk *b, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (b->len < 2)
		return (0);
	i = b->len - 1;
	tmp = b->stk[i];
	while (i > 0)
	{
		b->stk[i] = b->stk[i - 1];
		i--;
	}
	b->stk[0] = tmp;
	i = b->len - 1;
	tmp = b->rank[i];
	while (i > 0)
	{
		b->rank[i] = b->rank[i - 1];
		i--;
	}
	b->rank[0] = tmp;
	if (mode == 1)
		res->result[res->place] = 7;
	return (1);
}

int	rrr(t_stk *a, t_stk *b, t_res *res)
{
	int	i;
	int	j;

	i = rra(a, 0, res);
	j = rrb(b, 0, res);
	res->result[res->place] = 8;
	return (1);
}
