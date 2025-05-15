/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:17:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/14 20:36:25 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stk *A, int mode)
{
	int	tmp;
	int	i;

	if (A->len < 2)
		return ;
	tmp = A->stk[0];
	i = 0;
	while (i < A->len - 1)
	{
		A->stk[i] = A->stk[i + 1];
		i++;
	}
	A->stk[i] = tmp;
	if (mode == 1)
		write(1, "ra\n", 3);
}

void	rb(t_stk *B, int mode)
{
	int	tmp;
	int	i;

	if (B->len < 2)
		return ;
	tmp = B->stk[0];
	i = 0;
	while (i < B->len - 1)
	{
		B->stk[i] = B->stk[i + 1];
		i++;
	}
	B->stk[i] = tmp;
	if (mode == 1)
		write(1, "rb\n", 3);
}

void	rr(t_stk *A, t_stk *B)
{
	ra(A, 0);
	rb(B, 0);
	write(1, "rr\n", 3);
}
