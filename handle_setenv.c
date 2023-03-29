/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:42:33 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/29 17:04:56 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_setenv(t_mish *meta)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup(meta->cmd->pot[0]);
	key[ft_findchar(meta->cmd->pot[0], '=')] = '\0';
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], key, ft_strlen(key)))
		{
			ft_free((void **) &(key));
			ft_free((void **) &(meta->env[i]));
			meta->env[i] = ft_strdup(meta->cmd->pot[0]);
			return ;
		}
		i++;
	}
	if (ft_envlst_retvalue(meta->ext_env, key))
		ft_envlst_newvalue(meta->ext_env, key, meta->cmd->pot[0]);
	else
		ft_envlst_addfront(&(meta->ext_env), ft_envlst_new(meta->cmd->pot[0]));
	ft_free((void **) &(key));
}

int	ft_isasetenv(char *str)
{
	int	i;

	i = 0;
	while (ft_isenv(str[i]))
			i++;
	if (i == 0)
		return (0);
	if (str[i] == '=')
		return (1);
	return (0);
}