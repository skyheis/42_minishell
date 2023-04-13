/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:23:16 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 17:41:56 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_pipe(t_mish *meta, t_cmd *node, int fd_in, int fd_out)
{
	int	stat;
	int	pid;
	int	pexit;

	pid = fork();
	if (!pid)
	{
		stat = ft_do_red(meta, node);
		if (stat)
			exit(stat);
		ft_redirect(meta, fd_in, fd_out);
		pexit = ft_handle_commands(meta, node);
		ft_close_n_ret(fd_in, fd_out, -1, -2);
		ft_free_shell(meta);
		exit(pexit);
	}
	wait(&stat);
	if (stat == 65280)
		return (-1);
	pexit = WEXITSTATUS(stat);
	return (pexit);
}

int	ft_mini_pipe(t_mish *meta, t_cmd *node, int fd_write)
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
		ft_mini_pipe(meta, node->next, pp[1]);
	}
	if (pp[1] != -1)
		close(pp[1]);
	return (ft_exec_pipe(meta, node, pp[0], fd_write));
}

int	ft_pipe_or_not(t_mish *meta, t_cmd *node)
{
	signal(SIGINT, ft_sign_handler_exec);
	if (node->next)
		return (ft_mini_pipe(meta, node, 1)); 
	else
	{
		meta->exit_code = ft_do_red(meta, node);
		if (meta->exit_code)
			return (meta->exit_code);
		ft_redirect(meta, -1, -1);
		meta->exit_code = ft_handle_commands(meta, node);
		ft_rev_redirect(meta);
		return (meta->exit_code);
	}
}
