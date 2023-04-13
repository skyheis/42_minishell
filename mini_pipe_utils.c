/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:23:16 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 19:18:50 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (ret_num == -2)
		return (0);
	return (ret_num);
}

void	ft_redirect(t_mish *meta, int fd_in, int fd_out)
{
	if (meta->infile != -2)
		dup2(meta->infile, 0);
	else if (fd_in != -1)
		dup2(fd_in, 0);
	if (meta->outfile != -2)
		dup2(meta->outfile, 1);
	else if (fd_out != -1)
		dup2(fd_out, 1);
}

void	ft_red_fromfile(t_mish *meta)
{
	if (meta->infile != -2)
		dup2(meta->infile, 0);
	if (meta->outfile != -2)
		dup2(meta->outfile, 1);
}

void	ft_rev_redirect(t_mish *meta)
{
	if (meta->infile != -2)
	{
		close(meta->infile);
		meta->infile = -2;
		dup2(meta->c_stdin, 0);
	}
	if (meta->outfile != -2)
	{
		close(meta->outfile);
		meta->outfile = -2;
		dup2(meta->c_stdout, 1);
	}
}
