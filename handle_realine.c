/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_realine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:30:09 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/29 15:26:52 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printnodes(t_cmd *cmd, t_mish *meta)
{
	int	i = 0;
	(void)meta;

	while (cmd)
	{
		i = 0;
		while (cmd->pot[i])
		{
			printf("%s\n", cmd->pot[i]);
			i++;
		}
		printf("\nNEEXT\n");
		cmd = cmd->next;
	}
}

void	ft_handle_line(t_mish *meta)
{
	int		i;
	char	**mat;

	i = 0;
	// if dopo spazi subito | allora exit with error
	meta->flag = 1;
	while (meta->flag)
	{
		meta->flag = 0;
		if (i != 0 && meta->line[i] == '|')
			i++;
		//if (meta->line[i] == '|')
		//	i++;
		mat = ft_splitermux(&meta->line[i], meta);
		ft_cmdlst_addfront(&meta->cmd, ft_cmdlst_new(mat));
		while (meta->line[i] && meta->line[i] != '|')
		{
			if (meta->line[i] && meta->line[i] == SQUT)
			{
				i++;
				while (meta->line[i] && meta->line[i] != SQUT)
					i++;
			}
			if  (meta->line[i] && meta->line[i] == DQUT)
			{
				i++;
				while (meta->line[i] && meta->line[i] != DQUT)
					i++;
			}
			i++;
		}
	}
	ft_cmdlst_iterstr(meta->cmd, ft_parse_word, meta);
	meta->cmd_head = meta->cmd;
	//ft_printnodes(meta->cmd, meta);
}
