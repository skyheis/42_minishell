/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:38:50 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/23 11:35:59 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tutte da testare

/* esegue una funzine su tutte le stringhe */
void	ft_cmdlst_iterstr(t_cmd *cmd,
		void(*parse)(char *, t_mish *), t_mish *meta)
{
	int i;

	while (cmd)
	{
		i = 0;
		while (cmd->pot[i])
		{
			(*parse)(cmd->pot[i], meta);
			i++;
		}
		cmd = cmd->next;
	}
}

/* pulisce tutta la lista */
void	ft_cmdlst_clear(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		ft_free_matrix(&((*cmd)->pot));
		ft_free((void **) cmd);
		(*cmd) = tmp;
	}
}

/* aggiunge nodo davanti */
void	ft_cmdlst_addfront(t_cmd **cmd, t_cmd *new)
{
	new->next = *cmd;
	*cmd = new;
}

/* crea nuovo nodo */
t_cmd	*ft_cmdlst_new(char **pot)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->pot = pot;
	new->next = NULL;
	return (new);
}