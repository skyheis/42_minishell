/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:23:16 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/31 14:48:27 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	mini_pipe(t_mish *meta, t_cmd *node, int fd_write)
{
	int	pp[2];

	if (node->next)
	{
		pipe(pp);
		mini_pipe(meta, node->next, pp[1]);
	}
	else
	close(pp[1]);
	dup2(pp[0], 0);
	ft_handle_commands(meta, node);
}*/

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

void	ft_redirect(int fd_in, int fd_out)
{
	if (fd_in != -1)
		dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
}

int	ft_exec_pipe(t_mish *meta, t_cmd *node, int fd_in, int fd_out)
{
	int	stat;
	int	pid;
	int	pexit;

	pid = fork();
	if (!pid)
	{
		ft_redirect(fd_in, fd_out);
		pexit = ft_handle_commands(meta, node);
		ft_close_n_ret(fd_in, fd_out, -1, -2);
		ft_free_shell(meta);
		exit(pexit);
	}
	wait(&stat);
	//ft_close_n_ret(fd_in, -1, -1, -2);
	if (stat == 65280)
		return (-1);
	pexit = WEXITSTATUS(stat);
	return (pexit);
}

int	mini_pipe(t_mish *meta, t_cmd *node, int fd_write)
{
	int		pp[2];

	if (!node->next)
	{
		pp[1] = -1;
		pp[0] = meta->c_stdin;
	}
	else
	{
		pipe(pp);
		mini_pipe(meta, node->next, pp[1]);
	}
	if (pp[1] != -1)
		close(pp[1]);
	return (ft_exec_pipe(meta, node, pp[0], fd_write));
}

int	ft_pipe_or_not(t_mish *meta, t_cmd *node)
{
	if (node->next)
		return (mini_pipe(meta, node, 1)); 
	else
	{
		//posto per redirect
		return (ft_handle_commands(meta, node));
	}
}
