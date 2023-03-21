/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:00:27 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/03 22:02:43 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_heredoc(char *delimiter)
{
	char	*nline;
	size_t	delimiter_size;
	int		fd_gg;

	unlink("/tmp/ggiannit_ugly_pipex");
	fd_gg = open("/tmp/ggiannit_ugly_pipex",
			O_WRONLY | O_CREAT, 0644);
	delimiter_size = ft_strlen(delimiter) + 1;
	ft_putstr_fd("pipe heredoc> ", 1);
	delimiter = ft_strjoin(delimiter, "\n");
	nline = get_next_line(0);
	while (ft_strncmp(delimiter, nline, delimiter_size))
	{
		ft_putstr_fd(nline, fd_gg);
		ft_free_null(&nline);
		ft_putstr_fd("pipe heredoc> ", 1);
		while (!nline)
			nline = get_next_line(0);
	}
	close(fd_gg);
	get_next_line(-42);
	ft_free_null(&nline);
	ft_free_null(&delimiter);
	return (open("/tmp/ggiannit_ugly_pipex", O_RDONLY));
}
