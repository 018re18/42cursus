/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:02:44 by rookuma           #+#    #+#             */
/*   Updated: 2025/05/22 21:14:52 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_ati
{
	int		i;
	int		j;
	long	num;
}			t_ati;

typedef struct s_stk
{
	int		*rank;
	int		*stk;
	int		len;
}			t_stk;

typedef struct s_res
{
	int		result[8000];
	int		place;
	int		min;
	int		max;

}			t_res;

typedef struct s_cnk
{
	int		size;
	int		num;
	int		min;
	int		max;
}			t_cnk;

typedef struct s_AtB
{
	int		u_or_d;
	int		count;
	int		time;
	int		idx;
}			t_AtB;

int			sa(t_stk *A, int mode, t_res *res);
int			sb(t_stk *B, int mode, t_res *res);
int			ss(t_stk *A, t_stk *B, t_res *res);
int			pa(t_stk *A, t_stk *B, t_res *res);
int			pb(t_stk *A, t_stk *B, t_res *res);
int			ra(t_stk *A, int mode, t_res *res);
int			rb(t_stk *B, int mode, t_res *res);
int			rr(t_stk *A, t_stk *B, t_res *res);
int			rra(t_stk *A, int mode, t_res *res);
int			rrb(t_stk *B, int mode, t_res *res);
int			rrr(t_stk *A, t_stk *B, t_res *res);
void		ft_quick_sort(int *stk, int min, int max);
void		get_sortstk_rank(t_stk *A, int argc);
int			ft_atoi_sp(char *str, int *error);
int			*get_stkA(int argc, char **argv);
int			prepare(int argc, char **argv, t_stk *A, t_stk *B);
int			check_same(int *stk, int len);
void		sort_rank(t_stk *cpy, t_stk *A, int len);
void		slice_sort(t_stk *A, t_stk *B, t_res *res);
void		check_rrr(int *res);
void		put_res(int *res);

#endif
