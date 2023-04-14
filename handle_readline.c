/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:30:09 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 09:42:47 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* debug
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
}*/
/* ft_printnodes(meta->cmd, meta); */

static void	ft_skip_cmd(t_mish *meta, int *i)
{
	while (meta->line[*i] && meta->line[*i] != '|')
	{
		if (meta->line[*i] && meta->line[*i] == SQUT)
		{
			*i += 1;
			while (meta->line[*i] && meta->line[*i] != SQUT)
				*i += 1;
		}
		if (meta->line[*i] && meta->line[*i] == DQUT)
		{
			*i += 1;
			while (meta->line[*i] && meta->line[*i] != DQUT)
				*i += 1;
		}
		*i += 1;
	}
}

void	ft_handle_line(t_mish *meta)
{
	int		i;
	char	**mat;

	i = 0;
	meta->flag = 1;
	while (meta->flag)
	{
		meta->flag = 0;
		if (i != 0 && meta->line[i] == '|')
			i++;
		mat = ft_splitermux(&meta->line[i], meta);
		ft_cmdlst_addfront(&meta->cmd, ft_cmdlst_new(mat));
		meta->cmd->red = ft_splitered(&meta->line[i], meta);
		ft_skip_cmd(meta, &i);
	}
	ft_cmdlst_iterstr(meta->cmd, ft_parse_word, ft_parse_red, meta);
}
