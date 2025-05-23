/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:17:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:35:30 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra(t_stk *a, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (a->len < 2)
		return (0);
	tmp = a->stk[0];
	i = 0;
	while (i < a->len - 1)
	{
		a->stk[i] = a->stk[i + 1];
		i++;
	}
	a->stk[i] = tmp;
	tmp = a->rank[0];
	i = 0;
	while (i < a->len - 1)
	{
		a->rank[i] = a->rank[i + 1];
		i++;
	}
	a->rank[i] = tmp;
	if (mode == 1)
		res->result[res->place] = 3;
	return (1);
}

int	rb(t_stk *b, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (b->len < 2)
		return (0);
	tmp = b->stk[0];
	i = 0;
	while (i < b->len - 1)
	{
		b->stk[i] = b->stk[i + 1];
		i++;
	}
	b->stk[i] = tmp;
	tmp = b->rank[0];
	i = 0;
	while (i < b->len - 1)
	{
		b->rank[i] = b->rank[i + 1];
		i++;
	}
	b->rank[i] = tmp;
	if (mode == 1)
		res->result[res->place] = 4;
	return (1);
}

int	rr(t_stk *a, t_stk *b, t_res *res)
{
	int	i;
	int	j;

	i = ra(a, 0, res);
	j = rb(b, 0, res);
	res->result[res->place] = 5;
	return (1);
}
