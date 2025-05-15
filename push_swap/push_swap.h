/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:02:44 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/14 20:51:27 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_stk
{
	int	*rank;
	int	*stk;
	int	len;
}		t_stk;

void	sa(t_stk *A, int mode);
void	sb(t_stk *B, int mode);
void	ss(t_stk *A, t_stk *B);
void	pa(t_stk *A, t_stk *B);
void	pb(t_stk *A, t_stk *B);
void	ra(t_stk *A, int mode);
void	rb(t_stk *B, int mode);
void	rr(t_stk *A, t_stk *B);
void	rra(t_stk *A, int mode);
void	rrb(t_stk *B, int mode);
void	rrr(t_stk *A, t_stk *B);
void	quick_sort(int *stk, int min, int max);
t_stk	get_sortstk_rank(t_stk *A, int argc);
int		ft_atoi_sp(char *str, int *error);
int		*get_stkA(int argc, char **argv);
int		check_same(int *stk, int len);
void	sort_rank(t_stk *cpy, t_stk *A, int len);

#endif
