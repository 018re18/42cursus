/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:37:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 14:56:21 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_stk *A, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (A->len < 2)
		return (0);
	i = A->len - 1;
	tmp = A->stk[i];
	while (i > 0)
	{
		A->stk[i] = A->stk[i - 1];
		i--;
	}
	A->stk[0] = tmp;
	i = A->len - 1;
	tmp = A->rank[i];
	while (i > 0)
	{
		A->rank[i] = A->rank[i - 1];
		i--;
	}
	A->rank[0] = tmp;
	if (mode == 1)
		res->result[res->place] = 6;
	return (1);
}

int	rrb(t_stk *B, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (B->len < 2)
		return (0);
	i = B->len - 1;
	tmp = B->stk[i];
	while (i > 0)
	{
		B->stk[i] = B->stk[i - 1];
		i--;
	}
	B->stk[0] = tmp;
	i = B->len - 1;
	tmp = B->rank[i];
	while (i > 0)
	{
		B->rank[i] = B->rank[i - 1];
		i--;
	}
	B->rank[0] = tmp;
	if (mode == 1)
		res->result[res->place] = 7;
	return (1);
}

int	rrr(t_stk *A, t_stk *B, t_res *res)
{
	int	i;
	int	j;

	i = rra(A, 0, res);
	j = rrb(B, 0, res);
	res->result[res->place] = 8;
	return (1);
}
