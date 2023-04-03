/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:29:27 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/03 17:14:43 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_heredoc(t_mish *meta, char *delimiter)
{
	char	*nline;
	size_t	delimiter_size;

	//unlink("~/.heredoc");
	if (!delimiter[0])
		return (0);
	if (delimiter[0] == 32)
		delimiter[0] == '\0';
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
	return (1);
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
				return (ft_do_red(meta));

		else if (node->red[i][0] == '<')
			//infile
		else if (node->red[i][0] == '>' && node->red[i][1] == '>')
			//append
		else if (node->red[i][1] == '>')
			//create
	}
	return (0);
}
