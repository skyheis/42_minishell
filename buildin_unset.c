/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:27:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:54:18 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_list(t_mish *meta, t_cmd *node)
{
	int		k;
	t_exenv	*ino;

	k = 0;
	while (++k)
	{
		ino = meta->ext_env;
		while (ino)
		{
			if (!ft_strncmp(ino->key, node->pot[k],
					ft_findchar(node->pot[k], '='))
				&& !ft_strncmp(ino->key, node->pot[k], ft_strlen(ino->key)))
			{
				ft_free((void **) &(ino->key));
				ft_free((void **) &(ino->value));
				break ;
			}
			ino = ino->next;
		}
	}
}

void	ft_unset(t_mish *meta, t_cmd *node)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (meta->env[++i])
	{
		j = 0;
		while (node->pot[++j])
		{
			len = ft_strlen(node->pot[j]);
			if (!ft_strncmp(meta->env[i], node->pot[j], len))
				if (meta->env[i][len] == '=')
					meta->env = ft_matrixdel(meta->env, node->pot[j]);
		}
	}
	ft_unset_list(meta, node);
}
