/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:30:09 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/06 15:21:16 by ggiannit         ###   ########.fr       */
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
		printf("[[[[POT]]]]\n");
		while (cmd->pot[i])
		{
			printf("%i %s\n", i, cmd->pot[i]);
			i++;
		}
		i = 0;
		printf("[[[[RED]]]]\n");
		while (cmd->red[i])
		{
			printf("%i %s\n", i, cmd->red[i]);
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
		meta->cmd->red = ft_splitered(&meta->line[i], meta);
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
	//ft_printnodes(meta->cmd, meta);
	ft_cmdlst_iterstr(meta->cmd, ft_parse_word, ft_parse_red, meta);
	//ft_printnodes(meta->cmd, meta);
	//exit(0);
}
