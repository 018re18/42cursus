/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:51 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/23 12:35:48 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_stk *a, int mode, t_res *res)
{
	int	tmp;

	if (a->len < 2)
		return (0);
	tmp = a->stk[0];
	a->stk[0] = a->stk[1];
	a->stk[1] = tmp;
	tmp = a->rank[0];
	a->rank[0] = a->rank[1];
	a->rank[1] = tmp;
	if (mode == 1)
		res->result[res->place] = 9;
	return (1);
}

int	sb(t_stk *b, int mode, t_res *res)
{
	int	tmp;

	if (b->len < 2)
		return (0);
	tmp = b->stk[0];
	b->stk[0] = b->stk[1];
	b->stk[1] = tmp;
	tmp = b->rank[0];
	b->rank[0] = b->rank[1];
	b->rank[1] = tmp;
	if (mode == 1)
		res->result[res->place] = 10;
	return (1);
}

int	ss(t_stk *a, t_stk *b, t_res *res)
{
	int	i;
	int	j;

	i = sa(a, 0, res);
	j = sb(b, 0, res);
	res->result[res->place] = 11;
	return (1);
}

int	pa(t_stk *a, t_stk *b, t_res *res)
{
	int	i;

	if (b->len < 1)
		return (0);
	i = a->len;
	while (i > 0)
	{
		a->stk[i] = a->stk[i - 1];
		a->rank[i] = a->rank[i - 1];
		i--;
	}
	a->stk[0] = b->stk[0];
	a->rank[0] = b->rank[0];
	a->len++;
	i = 0;
	while (i < b->len - 1)
	{
		b->stk[i] = b->stk[i + 1];
		b->rank[i] = b->rank[i + 1];
		i++;
	}
	b->len--;
	res->result[res->place] = 1;
	return (1);
}

int	pb(t_stk *a, t_stk *b, t_res *res)
{
	int	i;

	if (a->len < 1)
		return (0);
	i = b->len;
	while (i > 0)
	{
		b->stk[i] = b->stk[i - 1];
		b->rank[i] = b->rank[i - 1];
		i--;
	}
	b->stk[0] = a->stk[0];
	b->rank[0] = a->rank[0];
	b->len++;
	i = 0;
	while (i < a->len - 1)
	{
		a->stk[i] = a->stk[i + 1];
		a->rank[i] = a->rank[i + 1];
		i++;
	}
	a->len--;
	res->result[res->place] = 2;
	return (1);
}
