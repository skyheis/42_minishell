/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:01:19 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 18:04:09 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_matrixlen(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}

int	ft_findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	ft_envlst_statusvalue(t_exenv *exenv, char *key)
{
	int	len;

	len = ft_strlen(key) + 1;
	while (exenv)
	{
		if (!ft_strncmp(key, exenv->key, len))
		{
			if (exenv->value)
				return (2);
			return (1);
		}
		exenv = exenv->next;
	}
	return (0);
}

char	*ft_envlst_retvalue(t_exenv *exenv, char *key)
{
	int	len;

	len = ft_strlen(key) + 1;
	while (exenv)
	{
		if (!ft_strncmp(key, exenv->key, len))
			return (exenv->value);
		exenv = exenv->next;
	}
	return (NULL);
}

void	ft_envlst_newvalue(t_exenv *exenv, char *key, char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(key) + 1;
	while (exenv)
	{
		if (!ft_strncmp(key, exenv->key, len))
		{
			while (str[i] != '=')
				i++;
			ft_free((void **) &(exenv->value));
			exenv->value = ft_substr(str, i + 1, ft_strlen(&str[i]));
			break ;
		}
		exenv = exenv->next;
	}
}
