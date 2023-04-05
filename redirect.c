/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:29:27 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/04 12:29:17 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1 append, 2 create */
int	ft_out_file(t_mish *meta, char *filename, int type)
{
	if (!filename[0])
		return (0);
	if (meta->outfile != -2)
		close(meta->outfile);
	if (type == 1)
		meta->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == 2)
		meta->outfile = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

int	ft_in_file(t_mish *meta, char *filename)
{
	if (!filename[0])
	{
		printf("hiroshell: syntax error near unexpected token `newline'");
		meta->exit_code = 2;
		return (0);
	}
	if (meta->infile != -2)
		close(meta->infile);
	meta->infile = open(filename, O_RDONLY);
	if (meta->infile)
	{
		perror(filename);
		meta->exit_code = 1;
		return (0);
	}
	return (1);
}

int	ft_in_heredoc(t_mish *meta, char *delimiter)
{
	char	*nline;
	size_t	delimiter_size;

	//unlink("~/.heredoc");
	if (!delimiter[0])
		return (0);
	if (delimiter[0] == 32)//non ricordo boh lol
		delimiter[0] == '\0'; //how knows
	if (meta->infile != -2)
		close(meta->infile);
	meta->infile = open("~/.heredoc", O_WRONLY | O_CREAT, 0644);
	delimiter_size = ft_strlen(delimiter) + 1;
	delimiter = ft_strjoin(delimiter, "\n");
	ft_putstr_fd("heredoc> ", 1);
	nline = get_next_line(0);
	while (ft_strncmp(delimiter, nline, delimiter_size))
	{
		ft_putstr_fd(nline, meta->infile);
		ft_free_null(&nline);
		ft_putstr_fd("heredoc> ", 1);
		while (!nline)
			nline = get_next_line(0);
	}
	close(meta->infile);
	get_next_line(-42);
	ft_free_null(&nline);
	ft_free_null(&delimiter);
	meta->infile = open("~/.heredoc", O_RDONLY); 
	return (1); //ricordati di cancellare .heredoc
}

int	ft_red_error(t_mish *meta)
{
	printf("hiroshell: syntax error near unexpected token `newline'");
	meta->exit_code = 2;
	return (2);
}

int	ft_do_red(t_mish *meta, t_cmd *node)
{
	int	i;
	int	len;

	i = -1;
	while (node->red && node->red[++i])
	{
		len = ft_strlen(node->red[i]);
		if (node->red[i][0] == '<' && node->red[i][1] == '<')
			if (!ft_in_heredoc(meta, &node->red[i][2]))
				return (ft_red_error(meta));
		else if (node->red[i][0] == '<')
			if (!ft_in_file(meta, &node->red[i][1]))
				return (1);
		else if (node->red[i][0] == '>' && node->red[i][1] == '>')
			if (!ft_out_file(meta, &node->red[i][2], 1))
				return (ft_red_error(meta));
		else if (node->red[i][1] == '>')
			if (!ft_out_file(meta, &node->red[i][1], 2))
				return (ft_red_error(meta));
	}
	return (0);
}
