/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:38:50 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/24 17:17:40 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tutte da testare

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
		ft_free((void **) exenv);
		(*exenv) = tmp;
	}
}

/* aggiunge nodo davanti */
void	ft_envlst_addfront(t_exenv **exenv, t_exenv *new)
{
	new->next = *exenv;
	*exenv = new;
}

/* crea nuovo nodo ----- forse da freeare str? */
t_exenv	*ft_envlst_new(char *str)
{
	t_exenv	*new;
	//char	*tmp;
	int	i;	

	new = malloc(sizeof(t_exenv));
	if (!new)
		return (NULL);
	//tmp = ft_strdup(str);
	while (str && str[i])
	{
		if (str[i] == '=')
		{
			new->key = ft_substr(str, 0, i);
			new->value = ft_substr(str, i + 1, ft_strlen(&str[i]));
			break ;
		}
		i++;
	}
	new->next = NULL;
	ft_free((void **) &str);
	return (new);
}
