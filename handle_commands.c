/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:19:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 19:31:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_shell(char **envp, t_mish *meta)
{
	char	*clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve("/usr/bin/clear", clean_path, envp);
		ft_free_shell(meta);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
	ft_print_file(meta, "badge/badge.bdg");
	ft_printf("\n");
}

void	ft_chad(t_mish *meta)
{
	static int	i = 0;

	if (i > 5)
		i = 0;
	if (i == 0)
		ft_print_file(meta, "badge/chad3.bdg");
	else if (i == 1)
		ft_print_file(meta, "badge/chad1.bdg");
	else if (i == 2)
		ft_print_file(meta, "badge/chad0.bdg");
	else if (i == 3)
		ft_print_file(meta, "badge/chad2.bdg");
	else if (i == 4)
		ft_print_file(meta, "badge/younow.bdg");
	else if (i == 5)
		ft_print_file(meta, "badge/sponge.bdg");
	i++;
}

int	ft_handle_commands_continue(t_mish *meta, t_cmd *node)
{
	int	ecode;

	ecode = 0;
	if (!ft_strncmp(node->pot[0], "clear", 6))
		ft_clean_shell(meta->env, meta);
	else if (!ft_strncmp(node->pot[0], "export", 7))
		ft_export(meta, node);
	else if (!ft_strncmp(node->pot[0], "chad", 5))
		ft_chad(meta);
	else if (!ft_strncmp(node->pot[0], "duck", 5))
		ecode = ft_duck(meta);
	else if (ft_isasetenv(node->pot[0]))
		ft_handle_setenv(meta, node);
	else if (node->pot[0])
		ecode = ft_execbin(meta, node);
	return (ecode);
}

int	ft_handle_commands(t_mish *meta, t_cmd *node)
{
	int	ecode;

	ecode = 0;
	if (!ft_strncmp(node->pot[0], "history", 8))
		ft_history(meta, node);
	else if (!ft_strncmp(node->pot[0], "exit", 5))
		return (-1);
	else if (!ft_strncmp(node->pot[0], "echo", 5))
		ft_echo(meta, node);
	else if (!ft_strncmp(node->pot[0], "unset", 5))
		ft_unset(meta, node);
	else if (!ft_strncmp(node->pot[0], "pwd", 4))
		ft_pwd(meta);
	else if (!ft_strncmp(node->pot[0], "env", 4))
		ft_env(meta, node);
	else if (!ft_strncmp(node->pot[0], "cd", 3))
		ecode = ft_cd(meta, node);
	else
		ecode = ft_handle_commands_continue(meta, node);
	return (ecode);
}
