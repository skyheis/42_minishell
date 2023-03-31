/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:08:38 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/29 15:17:07 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_mish *meta)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (meta->env[i])
	{
		j = 1;
		while (meta->cmd->pot[j])
		{
			len = ft_strlen(meta->cmd->pot[j]);
			if (!ft_strncmp(meta->env[i], meta->cmd->pot[j], len))
				if (meta->env[i][len] == '=')
					meta->env = ft_matrixdel(meta->env, meta->cmd->pot[j]);
			j++;
		}
		i++;
	}
}
