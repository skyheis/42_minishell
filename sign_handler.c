/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:28:42 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/17 09:42:00 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_magic_heredoc(int keepit)
{
	static int	pid = 0;

	if (pid)
	{
		kill(pid, SIGKILL);
		write(1, "\n", 1);
		pid = 0;
		return (1);
	}
	if (keepit)
		pid = keepit;
	return (0);
}

void	ft_sign_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_sign_ecode(NULL, 130);
		ft_magic_heredoc(0);
	}
}

void	ft_sign_ecode(t_mish *meta, int ecode)
{
	static t_mish	*versometa;

	if (meta)
		versometa = meta;
	else
		versometa->exit_code = ecode;
}

void	ft_sign_handler_exec(int sig)
{
	if (sig == SIGINT)
	{
		ft_sign_ecode(NULL, 130);
		write(1, "\n", 1);
	}
}

void	ft_sign_handler_rl(int sig)
{
	if (sig == SIGINT)
	{
		ft_sign_ecode(NULL, 130);
		write(1, "\n", 1);
		write(1, "\033[0;97m", 7);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
