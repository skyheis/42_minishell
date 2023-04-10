/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:51:33 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/10 19:54:54 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* nuova lista per export senza value?
 * forse basta fare che se value = NULL allora stampa, senno no
 * 
 * quando dichiara invece bisogna prima cercare se non c'e', se c'e' la aggiunge a env_list
 * */


void	ft_export(t_mish *meta, t_cmd *node)
{
	int	i;
	int	eq;
	char	*tmp;
	t_exenv *head;

	i = -1;
	if (!node->pot[1])
	{
		/* stampa env*/
		while (meta->env[++i])
		{
			eq = ft_findchar(meta->env[i], '=');
			tmp = ft_substr(meta->env[i], 0, eq);
			printf("declare -x %s=\"%s\"\n", tmp, &(meta->env[i][eq]));
			ft_free((void **) &tmp);
		}
		head = meta->ext_env;
		while (head)
		{
			if (!head->value)
				printf("declare -x %s\n", head->key);
			head = head->next;
		}
	}
	else
	{
		/* se non c'e' value o eq, cerca se nella lista c'e':
		 * se si aggiunge alla matrixe e libera quel nodo
		 * se no fa un addfront con solo key
		 * se c'e' env
		 * cerca se esiste in matrice
		 * se esite fa replace
		 * se no aggiunge alla matrice e cerca se esiste key in lista, in caso libera*/
	}
}
