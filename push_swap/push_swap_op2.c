/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:17:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 14:56:13 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra(t_stk *A, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (A->len < 2)
		return (0);
	tmp = A->stk[0];
	i = 0;
	while (i < A->len - 1)
	{
		A->stk[i] = A->stk[i + 1];
		i++;
	}
	A->stk[i] = tmp;
	tmp = A->rank[0];
	i = 0;
	while (i < A->len - 1)
	{
		A->rank[i] = A->rank[i + 1];
		i++;
	}
	A->rank[i] = tmp;
	if (mode == 1)
		res->result[res->place] = 3;
	return (1);
}

int	rb(t_stk *B, int mode, t_res *res)
{
	int	tmp;
	int	i;

	if (B->len < 2)
		return (0);
	tmp = B->stk[0];
	i = 0;
	while (i < B->len - 1)
	{
		B->stk[i] = B->stk[i + 1];
		i++;
	}
	B->stk[i] = tmp;
	tmp = B->rank[0];
	i = 0;
	while (i < B->len - 1)
	{
		B->rank[i] = B->rank[i + 1];
		i++;
	}
	B->rank[i] = tmp;
	if (mode == 1)
		res->result[res->place] = 4;
	return (1);
}

int	rr(t_stk *A, t_stk *B, t_res *res)
{
	int	i;
	int	j;

	i = ra(A, 0, res);
	j = rb(B, 0, res);
	res->result[res->place] = 5;
	return (1);
}
