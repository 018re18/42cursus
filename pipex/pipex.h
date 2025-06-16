/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:05:18 by rookuma           #+#    #+#             */
/*   Updated: 2025/06/13 16:39:22 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_ppx
{
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
	int		mode;
}			t_ppx;

typedef struct s_loop
{
	int		i;
	int		tmp_fd;
	pid_t	pid;
}			t_loop;

int			pipex_loop(int argc, char **argv, char **envp, t_ppx *x);
int			pipex_start_place(int mode);
char		*get_path(char *cmd, char **envp);
void		pipex_change_in_out(int argc, char **argv, t_ppx *x, t_loop *l);
int			ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin_path(char const *s1, char const *s2);
void		free_split(char **str);
void		perror_exit(const char *err, int status);
int			ft_strchr(char *s, char c);
char		**ft_split(char const *s, char c);

#endif
