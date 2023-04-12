/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duck.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:57:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/07 17:36:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_magic_duck(int keepit)
{
	static int	duck = 0;

	if (duck)
	{
		duck = 0;
		return (0);
	}
	if (keepit)
		duck = keepit;
	return (1);
}

void	ft_sign_handler_duck(int sig)
{
	if (sig == SIGINT)
		ft_magic_duck(1);
}

int	ft_duck(t_mish *meta)
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
	i = 0;
	while (ft_magic_duck(0))
	{
		ft_print_file(meta, fnames[i++]);
		usleep(110000);
		if (i == 55)
			i = 0;
	}
	ft_free_matrix(&fnames);
	signal(SIGINT, ft_sign_handler_exec);
	return (130);
}