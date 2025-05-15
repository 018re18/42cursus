/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:37:16 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/14 20:48:16 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stk *A, int mode)
{
	int	tmp;
	int	i;

	if (A->len < 2)
		return ;
	i = A->len - 1;
	tmp = A->stk[i];
	while (i > 0)
	{
		A->stk[i] = A->stk[i - 1];
		i--;
	}
	A->stk[0] = tmp;
	if (mode == 1)
		write(1, "rra\n", 4);
}

void	rrb(t_stk *B, int mode)
{
	int	tmp;
	int	i;

	if (B->len < 2)
		return ;
	i = B->len - 1;
	tmp = B->stk[i];
	while (i > 0)
	{
		B->stk[i] = B->stk[i - 1];
		i--;
	}
	B->stk[0] = tmp;
	if (mode == 1)
		write(1, "rrb\n", 4);
}

void	rrr(t_stk *A, t_stk *B)
{
	rra(A, 0);
	rrb(B, 0);
	write(1, "rrr\n", 4);
}
