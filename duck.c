/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duck.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:57:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/07 11:11:20 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_magic_duck(int keepit)
{
	static int	pid = 0;

	if (pid)
	{
		pid = 0;
		return (0);
	}
	if (keepit)
		pid = keepit;
	return (1);
}

void	ft_sign_handler_duck(int sig)
{
	if (sig == SIGINT) // ctrl-C
		ft_magic_duck(1);
}

void	ft_duck(t_mish *meta)
{
	int		i;
	int		fd;
	char	**fnames;

	i = 0;
	signal(SIGINT, ft_sign_handler_duck);
	fnames = ft_calloc(57, sizeof(char *));
	fd = open("dduck/dduck.lst", O_RDONLY);
	fnames[i] = get_next_line(fd);
	while (fnames[i++])
		fnames[i] = get_next_line(fd);
	i = -1;
	while (fnames[++i])
		fnames[i][ft_strlen(fnames[i]) - 1] = '\0';
	i = -1;
	while (ft_magic_duck(0))
	{
		ft_print_file(meta, fnames[i++]);
		usleep(110000);
		if (i == 56)
			i = -1;
	}
	ft_free_matrix(&fnames);
	signal(SIGINT, ft_sign_handler_exec);
}
