/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:51:33 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 13:06:59 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* nuova lista per export senza value?
 * forse basta fare che se value = NULL allora stampa, senno no
 * 
 * quando dichiara invece bisogna prima cercare se non c'e', se c'e' la aggiunge a env_list
 * */

void	ft_export_stamp(t_mish *meta)
{
	int		i;
	int		eq;
	char	*tmp;
	t_exenv	*head;

	i = -1;
	while (meta->env[++i])
	{
		eq = ft_findchar(meta->env[i], '=');
		tmp = ft_substr(meta->env[i], 0, eq);
		printf("declare -x %s=\"%s\"\n", tmp, &(meta->env[i][eq + 1]));
		ft_free((void **) &tmp);
	}
	head = meta->ext_env;
	while (head)
	{
		if (!head->value && head->key)
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

int		ft_key_iglliena(t_mish *meta, char *key)
{
	int		i;

	i = 0;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], key, ft_strlen(key)) && meta->env[i][ft_strlen(key)] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_mish *meta, t_cmd *node)
{
	int		i;
	int		k;
	char	*tmp;
	t_exenv	*ino;

	if (!node->pot[1])
		ft_export_stamp(meta);
	else
	{
		i = 0;
		k = 0;
		while (node->pot[++k])
		{
			while (ft_isenv(node->pot[k][i]))
				i++;
			if (node->pot[k][i] == '\0' ||
				(node->pot[k][i] == '=' && node->pot[k][i + 1] == '\0'))
			{
				if (ft_key_iglliena(meta, node->pot[k]))
					continue ;
				ino = meta->ext_env;
				while (ino)
				{
					if (!ft_strncmp(ino->key, node->pot[k], ft_findchar(node->pot[k], '=')) && !ft_strncmp(ino->key, node->pot[k], ft_strlen(ino->key)))// - 1))
					{
						if (ft_envlst_statusvalue(ino, ino->key) == 1)
							break ;
						tmp = ft_strjoin(ino->key, "=");
						tmp = ft_linejoin(tmp, ino->value, ft_strlen(ino->value));
						meta->env = ft_replace_add_env(meta->env, tmp);
						ft_free((void **) &(ino->key));
						ft_free((void **) &(ino->value));
						break ;
					}
					ino = ino->next;
				}
				if (!ino)
					ft_envlst_addfront(&meta->ext_env, ft_envlst_new(node->pot[k]));
			}
			else
			{
				meta->env = ft_replace_add_env(meta->env, ft_strdup(node->pot[k]));
				ino = meta->ext_env;
				while (ino)
				{
					if (!ft_strncmp(ino->key, node->pot[k], ft_findchar(node->pot[k], '=')) && !ft_strncmp(ino->key, node->pot[k], ft_strlen(ino->key)))
					{
						ft_free((void **) &(ino->key));
						ft_free((void **) &(ino->value));
						break ;
					}
					ino = ino->next;
				}
			}
		}
	}
}
