/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:51 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/18 19:14:22 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stk *A, int mode)
{
	int	tmp;

	if (A->len < 2)
		return ;
	tmp = A->stk[0];
	A->stk[0] = A->stk[1];
	A->stk[1] = tmp;
	tmp = A->rank[0];
	A->rank[0] = A->rank[1];
	A->rank[1] = tmp;
	if (mode == 1)
		write(1, "sa\n", 3);
}

void	sb(t_stk *B, int mode)
{
	int	tmp;

	if (B->len < 2)
		return ;
	tmp = B->stk[0];
	B->stk[0] = B->stk[1];
	B->stk[1] = tmp;
	tmp = B->rank[0];
	B->rank[0] = B->rank[1];
	B->rank[1] = tmp;
	if (mode == 1)
		write(1, "sb\n", 3);
}

void	ss(t_stk *A, t_stk *B)
{
	sa(A, 0);
	sb(B, 0);
	write(1, "ss\n", 3);
}

void	pa(t_stk *A, t_stk *B)
{
	int	i;

	if (B->len < 1)
		return ;
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
	write(1, "pa\n", 3);
}

void	pb(t_stk *A, t_stk *B)
{
	int	i;

	if (A->len < 1)
		return ;
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
	write(1, "pb\n", 3);
}
