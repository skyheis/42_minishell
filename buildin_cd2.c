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

int	ft_cd_meno(t_mish *meta)
{
	char	*tmp;

	tmp = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = ft_strdup(meta->olddir);
	ft_free((void **) &(meta->olddir));
	meta->olddir = tmp;
	printf("%s\n", meta->curdir);
	chdir(meta->curdir);
	return (1);
}

int	ft_cd_slash(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 0;
	if (node->pot[1][0] != '-')
	{
		ft_cd_slash2(meta, node);
		return (1);
	}
	if (node->pot[1][0] == '-' && (!node->pot[1][1] || node->pot[1][1] == 32))
		return (ft_cd_meno(meta));
	return (0);
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
	while(str[k] && str[k] != '/')
		meta->curdir[j++] = str[k++];
	meta->curdir = ft_strjoin_free(cwd, meta->curdir);
}

int	len_slash(char *str)
{
	int i;

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
	while (node->pot[1][i])
	{
		if (node->pot[1][i] && (!ft_strncmp(&node->pot[1][i], "..", 2) || (!ft_strncmp(&node->pot[1][i], "../", 3))))
		{
			ft_cd_pre(meta);
			chdir(meta->curdir);
			i += 3;
		}
		else if (node->pot[1][i] && ((ft_isalpha(node->pot[1][i]) || ft_isdigit(node->pot[1][i])) ||
			(!ft_strncmp(&node->pot[1][i], "./", 2) && (ft_isalpha(node->pot[1][i + 2])
				|| ft_isdigit(node->pot[1][i + 2])))))
		{
			if (!ft_strncmp(&node->pot[1][i], "./", 2))
				i += 2;
			chdir(&node->pot[1][i]);
			ft_next_slash(meta, &node->pot[1][i]);
			i += len_slash(&node->pot[1][i]);
			i++;
		}
		else
			i++;
	}
	return (1);
}

void	ft_cd_slash2(t_mish *meta, t_cmd *node)
{
	int	i;
	int	k;

	i = 1;
	ft_slash(meta);
	while (node->pot[1][i] && !ft_isalpha(node->pot[1][i])
		&& !ft_isdigit(node->pot[1][i]))
		i++;
	i--;
	while (node->pot[1][i])
	{
		if (!ft_strncmp(&node->pot[1][i], "..", 2) || (!ft_strncmp(&node->pot[1][i], "../", 3)))
		{
			k = 0;
			ft_find_path(meta->home_path, &k);
			chdir(&meta->home_path[k]);
			ft_cd_pre(meta);
			i += 3;
		}
		else if ((ft_isalpha(node->pot[1][i]) || ft_isdigit(node->pot[1][i])) ||
			(!ft_strncmp(&node->pot[1][i], "./", 2) && (ft_isalpha(node->pot[1][i + 2])
				|| ft_isdigit(node->pot[1][i + 2]))))
		{
			k = 0;
			if (!ft_strncmp(&node->pot[1][i], "./", 2))
				i += 2;
			ft_find_path(meta->home_path, &k);
			chdir(&meta->home_path[k]);
			ft_next_slash(meta, &node->pot[1][i]);
			i += len_slash(&node->pot[1][i]);
			i++;
		}
		else
			i++;
	}
}
