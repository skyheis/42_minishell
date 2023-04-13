/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:38:50 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 12:02:51 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tutte da testare

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

void	ft_envlst_nullnode(t_exenv *exenv, char *key)
{
	int	len;

	len = ft_strlen(key) + 1;
	while (exenv)
	{
		if (!ft_strncmp(key, exenv->key, len))
		{
			exenv->key = NULL;
			exenv->value = NULL;
			break ;
		}
		exenv = exenv->next;
	}
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

/* pulisce tutta la lista */
void	ft_envlst_clear(t_exenv **exenv)
{
	t_exenv	*tmp;

	tmp = NULL;
	while (*exenv)
	{
		tmp = (*exenv)->next;
		ft_free((void **) &((*exenv)->key));
		ft_free((void **) &((*exenv)->value));
		ft_free((void **) &(*exenv));
		(*exenv) = tmp;
	}
}

/* aggiunge nodo davanti */
void	ft_envlst_addfront(t_exenv **exenv, t_exenv *new)
{
	new->next = *exenv;
	*exenv = new;
}

/* crea nuovo nodo ----- forse da freeare str? post: non credo*/
t_exenv	*ft_envlst_new(char *str)
{
	t_exenv	*new;
	int	i;	

	i = 0;
	new = malloc(sizeof(t_exenv));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == '=')
		{
			new->key = ft_substr(str, 0, i);
			new->value = ft_substr(str, i + 1, ft_strlen(&str[i])); //se niente dopo = e' null o vuoto?
			break ;
		}
		i++;
	}
	if (!str[i])
	{
		new->key = ft_strdup(str);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}
