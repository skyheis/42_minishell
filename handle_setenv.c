/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:42:33 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:53:19 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isasetenv(char *str)
{
	int	i;

	i = 0;
	while (str && ft_isenv(str[i]))
		i++;
	if (i == 0)
		return (0);
	if (str && str[i] == '=')
		return (1);
	return (0);
}

void	ft_env_rbracket(char **vake)
{
	int		eq;
	char	*key;
	char	*tmp;

	eq = ft_findchar(*vake, '=');
	if ((*vake)[eq + 1] != '(' || (*vake)[ft_strlen(*vake) - 1] != ')')
		return ;
	key = ft_strdup(*vake);
	key[eq + 1] = '\0';
	tmp = ft_linejoin(key, &((*vake)[eq + 2]),
			ft_strlen(&((*vake)[eq + 2])) - 1);
	ft_free((void **) vake);
	*vake = tmp;
}

static void	ft_handle_setenv_list(t_mish *meta, t_cmd *node, char *key)
{
	if (ft_envlst_statusvalue(meta->ext_env, key) == 1)
	{
		meta->env = ft_replace_add_env(meta->env, strdup(node->pot[0]));
		ft_envlst_nullnode(meta->ext_env, key);
	}
	else if (ft_envlst_statusvalue(meta->ext_env, key) == 2)
		ft_envlst_newvalue(meta->ext_env, key, node->pot[0]);
	else
		ft_envlst_addfront(&(meta->ext_env), ft_envlst_new(node->pot[0]));
}

void	ft_handle_setenv(t_mish *meta, t_cmd *node)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup(node->pot[0]);
	key[ft_findchar(node->pot[0], '=')] = '\0';
	ft_env_rbracket(&(node->pot[0]));
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], key, ft_strlen(key))
			&& meta->env[i][ft_strlen(key)] == '=')
		{
			ft_free((void **) &(key));
			ft_free((void **) &(meta->env[i]));
			meta->env[i] = ft_strdup(node->pot[0]);
			return ;
		}
		i++;
	}
	ft_handle_setenv_list(meta, node, key);
	ft_free((void **) &(key));
}
