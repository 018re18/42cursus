/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:51 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 16:01:23 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_stk *A, int mode, t_res *res)
{
	int	tmp;
	
	if (A->len < 2)
		return (0);
	tmp = A->stk[0];
	A->stk[0] = A->stk[1];
	A->stk[1] = tmp;
	tmp = A->rank[0];
	A->rank[0] = A->rank[1];
	A->rank[1] = tmp;
	if (mode == 1)
		res->result[res->place] = 9;
	return (1);
}

int	sb(t_stk *B, int mode, t_res *res)
{
	int	tmp;

	if (B->len < 2)
		return (0);
	tmp = B->stk[0];
	B->stk[0] = B->stk[1];
	B->stk[1] = tmp;
	tmp = B->rank[0];
	B->rank[0] = B->rank[1];
	B->rank[1] = tmp;
	if (mode == 1)
		res->result[res->place] = 10;
	return (1);
}

int	ss(t_stk *A, t_stk *B, t_res *res)
{
	int	i;
	int	j;

	i = sa(A, 0, res);
	j = sb(B, 0, res);
	res->result[res->place] = 11;
	return (1);
}

int	pa(t_stk *A, t_stk *B, t_res *res)
{
	int	i;

	if (B->len < 1)
		return (0);
	i = A->len;
	while (i > 0)
	{
		A->stk[i] = A->stk[i - 1];
		A->rank[i] = A->rank[i - 1];
		i--;
	}
	A->stk[0] = B->stk[0];
	A->rank[0] = B->rank[0];
	A->len++;
	i = 0;
	while (i < B->len - 1)
	{
		B->stk[i] = B->stk[i + 1];
		B->rank[i] = B->rank[i + 1];
		i++;
	}
	B->len--;
	res->result[res->place] = 1;
	return (1);
}

int	pb(t_stk *A, t_stk *B, t_res *res)
{
	int	i;

	if (A->len < 1)
		return (0);
	i = B->len;
	while (i > 0)
	{
		B->stk[i] = B->stk[i - 1];
		B->rank[i] = B->rank[i - 1];
		i--;
	}
	B->stk[0] = A->stk[0];
	B->rank[0] = A->rank[0];
	B->len++;
	i = 0;
	while (i < A->len - 1)
	{
		A->stk[i] = A->stk[i + 1];
		A->rank[i] = A->rank[i + 1];
		i++;
	}
	A->len--;
	res->result[res->place] = 2;
	return (1);
}
