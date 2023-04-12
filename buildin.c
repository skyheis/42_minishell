/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:10:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/12 16:49:25 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mish *meta, t_cmd *node)
{
	int	flag;
	int	i;

	(void)meta;
	flag = ft_strncmp(node->pot[1], "-n\0", 3);
	i = 1;
	if (!flag)
		i++;
	while (node->pot[i])
	{
		if (!flag && !node->pot[i + 1])
			printf("%s", node->pot[i]);
		else
			printf("%s ", node->pot[i]);
		i += 1;
	}
	if (flag)
		printf("\n");
}

void	ft_pwd(t_mish *meta)
{
	printf("%s\n", meta->curdir);
}

void	ft_history(t_mish *meta, t_cmd *node)
{
	int		i;
	char	*hline;

	i = 1;
	close(meta->fd_history);
	if (!ft_strncmp(node->pot[1], "-c", 3))
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

void	ft_env(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 0;
	if (node->pot[1])
		return ;
	while (meta->env[i])
		printf("%s\n", meta->env[i++]);
}

void	ft_unset(t_mish *meta, t_cmd *node) //manca la parte della lista
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (meta->env[i])
	{
		j = 1;
		while (node->pot[j])
		{
			len = ft_strlen(node->pot[j]);
			if (!ft_strncmp(meta->env[i], node->pot[j], len))
				if (meta->env[i][len] == '=')
					meta->env = ft_matrixdel(meta->env, node->pot[j]);
			j++;
		}
		i++;
	}
}
