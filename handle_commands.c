/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:19:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/30 12:05:56 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mish *meta)
{
	int	flag;
	int	i;

	flag = ft_strncmp(meta->cmd->pot[1], "-n\0", 3);
	i = 1;
	if (!flag)
		i++;
	while (meta->cmd->pot[i])
	{
		if (!flag && !meta->cmd->pot[i + 1])
			printf("%s", meta->cmd->pot[i]);
		else
			printf("%s ", meta->cmd->pot[i]);
		i += 1;
	}
	if (flag)
		printf("\n");
}

void	ft_pwd(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			printf("%s\n", &meta->env[i][4]);
			return ;
		}
		i++;
	}
}

void	ft_history(t_mish *meta)
{
	int	i;
	char	*hline;

	i = 1;
	close(meta->fd_history);
	if (!ft_strncmp(meta->cmd->pot[1], "-c", 3))
	{
		unlink(meta->path_history);
		rl_clear_history();
	}
	meta->fd_history = open(meta->path_history,
		O_RDWR | O_CREAT | O_APPEND, 0644);
	hline = get_next_line(meta->fd_history);
	while (hline)
	{
		printf("%4i %s", i, hline);
		i++;
		ft_free((void **)&hline);
		hline = get_next_line(meta->fd_history);
	}
}

void	ft_env(t_mish *meta)
{
	int	i;

	i = 0;
	if (meta->cmd->pot[1])
		return ;
	while (meta->env[i])
		printf("%s\n", meta->env[i++]);
}



void	ft_clean_window(char **envp)
{
	char	*clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve("/usr/bin/clear", clean_path, envp);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
}


int	ft_handle_commands(t_mish *meta)
{
	while (meta->cmd)
	{
		if (!ft_strncmp(meta->cmd->pot[0], "history", 8))
			ft_history(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "exit", 5))
				return (1);
		else if (!ft_strncmp(meta->cmd->pot[0], "echo", 5))// caricare nuove envp ogni volta che cambio cartella  DA FARE!!
			ft_echo(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "unset", 5))
			ft_unset(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "pwd", 4))
			ft_pwd(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "env", 4))
			ft_env(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "cd", 3))
			ft_cd(meta);
		else if (!ft_strncmp(meta->cmd->pot[0], "clear", 6))
			ft_clean_window(meta->env);
		else if (ft_isasetenv(meta->cmd->pot[0]))
			ft_handle_setenv(meta);
		else if (meta->cmd->pot[0])
			ft_execbin(meta);
			//printf("%s: command not found\n", meta->cmd->pot[0]); //solo per test, poi sistemo
		meta->cmd = meta->cmd->next;
 	}
	return (0);
}
