/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:29:27 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/14 14:47:24 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1 append, 2 create */
int	ft_out_file(t_mish *meta, char *filename, int type)
{
	if (!filename[0])
		return (0);
	if (meta->outfile != -2 && meta->outfile != -1)
		close(meta->outfile);
	if (type == 1)
		meta->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == 2)
		meta->outfile = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (1);
}

int	ft_in_file(t_mish *meta, char *filename)
{
	if (!filename[0])
	{
		printf("duckshell: syntax error near unexpected token `newline'");
		meta->exit_code = 2;
		return (0);
	}
	if (meta->infile != -2 && meta->infile != -1)
	if (meta->infile != -2)
		close(meta->infile);
	meta->infile = open(filename, O_RDONLY);
	if (meta->infile <= 0)
	{
		perror(filename);
		meta->exit_code = 1;
		return (0);
	}
	return (1);
}

int	ft_red_continue(t_mish *meta, t_cmd *node, int i)
{
	if (node->red[i][0] == '<')
	{
		if (!ft_in_file(meta, &node->red[i][1]))
			return (2);
	}
	else if (node->red[i][0] == '>' && node->red[i][1] == '>')
	{
		if (!ft_out_file(meta, &node->red[i][2], 1))
			return (ft_red_error(meta));
	}
	else if (node->red[i][0] == '>')
	{
		if (!ft_out_file(meta, &node->red[i][1], 2))
			return (ft_red_error(meta));
	}
	return (0);
}

int	ft_do_red(t_mish *meta, t_cmd *node)
{
	int	i;
	int	ecode;

	i = -1;
	while (node->red && node->red[++i])
	{
		if (node->red[i][0] == '<' && node->red[i][1] == '<')
		{
			if (!node->red[i][2])
				return (ft_red_error(meta));
			if (!ft_in_heredoc(meta, &node->red[i][2]))
				return (130);
		}
		else
		{
			ecode = ft_red_continue(meta, node, i);
			if (ecode)
				return (ecode);
		}
	}
	return (0);
}
