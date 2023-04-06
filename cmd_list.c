/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:38:50 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/06 09:32:08 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tutte da testare

/* esegue una funzine su tutte le stringhe */
void	ft_cmdlst_iterstr(t_cmd *cmd, char *(*parse1)(char *, t_mish *),
		char *(*parse2)(char *, t_mish *), t_mish *meta)
{
	int i;

	while (cmd)
	{
		i = 0;
		while (cmd->pot && cmd->pot[i])
		{
			cmd->pot[i] = (*parse1)(cmd->pot[i], meta);
			i++;
		}
		i = 0;
		while (cmd->red && cmd->red[i])
		{
			cmd->red[i] = (*parse2)(cmd->red[i], meta);
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
		ft_free_matrix(&((*cmd)->red));
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
	new->red = 0;
	new->next = NULL;
	return (new);
}
