/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:28:42 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/01 16:30:23 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (sig == SIGINT) // ctrl-C
	{
		ft_sign_ecode(NULL, 130);
		write(1, "\n", 1);
	}
}

void	ft_sign_handler_rl(int sig)
{
	if (sig == SIGINT) // ctrl-C
	{
		ft_sign_ecode(NULL, 130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		
		rl_redisplay();
	}
}
