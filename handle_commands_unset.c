/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:08:38 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/31 10:37:14 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_mish *meta, t_cmd *node)
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
