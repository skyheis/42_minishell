/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:50:22 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:50:24 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_abs_path(t_mish *meta)
{
	ft_free((void **) &(meta->olddir));
	meta->olddir = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = ft_strdup(meta->home_path);
}

int	ft_find_path(char *str, int *k)
{
	int	j;
	int	find_slash;

	j = 0;
	find_slash = 0;
	while (str[j])
	{
		if (str[j] == '/')
		{
			*k = j;
			find_slash++;
		}
		j++;
	}
	if (find_slash == 1)
		return (-42);
	return (0);
}
