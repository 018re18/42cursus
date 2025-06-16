/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rookuma <rookuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:33:36 by rookuma           #+#    #+#             */
/*   Updated: 2025/06/12 18:43:22 by rookuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	mode_here_doc(const char *limiter)
{
	int		in_fd;
	char	*line;
	int		len;

	in_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_fd < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		len = ft_strlen(limiter);
		if (!line || (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n'))
			break ;
		write(in_fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(in_fd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ppx	x;
	int		status;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (1);
	}
	x.mode = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		x.mode = 1;
	if (x.mode == 1)
	{
		if (argc < 6)
		{
			write(2, "Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 47);
			return (1);
		}
		if (!mode_here_doc(argv[2]))
			return (1);
	}
	status = pipex_loop(argc, argv, envp, &x);
	if (x.mode == 1)
		unlink("here_doc");
	return (status);
}
