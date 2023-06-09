/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:55:57 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/17 09:49:51 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_if_exist_replace(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD=", 4))
		{
			ft_free((void **) &(meta->env[i]));
			meta->env[i] = ft_strjoin("PWD=", meta->curdir);
		}
		if (!ft_strncmp(meta->env[i], "OLDPWD=", 7))
		{
			ft_free((void **) &(meta->env[i]));
			meta->env[i] = ft_strjoin("OLDPWD=", meta->olddir);
		}
		i++;
	}
}

void	ft_cd_pre(t_mish *meta)
{
	int		j;
	int		k;
	char	*cwd;

	j = 0;
	k = 0;
	if (ft_find_path(meta->curdir, &k) == -42)
	{
		ft_slash(meta);
		return ;
	}
	cwd = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = (char *) ft_calloc(k + 1, sizeof(char));
	j = -1;
	while (++j < k)
		meta->curdir[j] = cwd[j];
	ft_free((void **) &cwd);
}

static void	ft_cd2_2_2(t_mish *meta, t_cmd *node, int flag)
{
	int	i;

	i = 0;
	if (!flag)
	{
		ft_free((void **) &(meta->olddir));
		meta->olddir = ft_strdup(meta->curdir);
		ft_find_path(meta->home_path, &i);
		chdir(&meta->home_path[i]);
		ft_cd_pre(meta);
		return ;
	}
	chdir(node->pot[1]);
	ft_pre_slash(meta, node);
}

int	ft_cd2(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 1;
	if (!ft_strncmp(node->pot[1], "..", 2))
	{
		while (node->pot[1][++i])
		{
			if (node->pot[1][i] && node->pot[1][i] != '/'
				&& (!ft_strncmp(&node->pot[1][i], "../", 3) ||
					node->pot[1][i] == '.'))
				return (ft_pre_slash(meta, node));
			else if (node->pot[1][i] && ((ft_isalpha(node->pot[1][i + 3])
				|| ft_isdigit(node->pot[1][i + 3])) ||
					(!ft_strncmp(&node->pot[1][i + 1], "./", 2)
						&& (ft_isalpha(node->pot[1][i + 3])
							|| ft_isdigit(node->pot[1][i + 3])))))
				return (ft_pre_slash(meta, node));
			else if (node->pot[1][i] && node->pot[1][i] != '/')
				return (1);
		}
		ft_cd2_2_2(meta, node, 0);
	}
	else
		ft_cd2_2_2(meta, node, -42);
	return (0);
}

int	ft_cd(t_mish *meta, t_cmd *node)
{
	if (!node->pot[1])
	{
		chdir(meta->home_path);
		ft_abs_path(meta);
	}
	else if (node->pot[1] && node->pot[2])
	{
		ft_putstr_fd("duckshell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (node->pot[1][0] != '-' && chdir(node->pot[1]) != 0)
	{
		perror("Error");
		return (1);
	}
	else if (node->pot[1][0] == '/' || node->pot[1][0] == '-')
	{
		ft_cd_slash(meta, node);
	}
	else
		ft_cd2(meta, node);
	ft_if_exist_replace(meta);
	return (0);
}
