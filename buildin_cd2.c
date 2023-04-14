/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:54:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:55:18 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_slash(t_mish *meta)
{
	ft_free((void **) &(meta->olddir));
	meta->olddir = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = ft_strdup("/");
}

void	ft_next_slash(t_mish *meta, char *str)
{
	int		j;
	int		k;
	char	*cwd;

	j = 0;
	k = 0;
	cwd = NULL;
	cwd = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = (char *) ft_calloc (ft_strlen(cwd)
			+ ft_strlen(str) + 1, sizeof(char));
	if (cwd[1] != '\0')
		meta->curdir[j++] = '/';
	while (str[k] && str[k] != '/')
		meta->curdir[j++] = str[k++];
	meta->curdir = ft_strjoin_free(cwd, meta->curdir);
}

int	len_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (i);
		i++;
	}
	return (i);
}

int	ft_pre_slash(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 0;
	ft_free((void **) &(meta->olddir));
	meta->olddir = ft_strdup(meta->curdir);
	if (!ft_strncmp(&node->pot[1][i], "..", 2)
		|| !ft_strncmp(&node->pot[1][i], "../", 3))
	{
		ft_find_path(meta->home_path, &i);
		chdir(&meta->home_path[i]);
		ft_cd_pre(meta);
		i = 3;
	}
	ft_pre_slash_2(meta, node, i);
	return (1);
}

void	ft_cd_slash2(t_mish *meta, t_cmd *node)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	ft_slash(meta);
	while (node->pot[1][i] && !ft_isalpha(node->pot[1][i])
		&& !ft_isdigit(node->pot[1][i]))
		i++;
	i--;
	ft_cd_slash2_2(meta, node, i, k);
}
