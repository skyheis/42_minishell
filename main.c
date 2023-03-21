/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 16:18:33 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_free
//ft_strjoin_free

int	ft_free_shell(t_mish *meta)
{
	ft_free_null(&(meta->context));
	return (1);
}

void	ft_clean_window(t_mish *meta)
{
	char *clean_path[2];

	(void) meta;
	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve(clean_path[0], clean_path, NULL);
		ft_free_null(clean_path);
		ft_free_shell(meta);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
}

int	ft_welcome_badge(t_mish *meta)
{
	int		fd;
	int		b_readed;
	char	*file_memory;
	char	*full_badge;

	(void) meta;
	printf("\e[1;1H\e[2J");
	fd = open("badge.bdg", O_RDONLY);
	b_readed = READ_SIZE;
	full_badge = NULL;
	if (fd == -1)
		return (0);
	while (b_readed == READ_SIZE)
	{
		file_memory = (char *) ft_calloc(READ_SIZE + 1, sizeof(char));
		b_readed = read(fd, file_memory, READ_SIZE);
		if (b_readed == -1)
			return (0);
		full_badge = ft_strjoin_free(full_badge, file_memory);
	}
	close(fd);
	printf("%s\nWelcome %s\n\n", full_badge, getenv("USER"));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_mish	meta;
	(void) ac;
	(void) av;
	(void) envp;

	meta.context = ft_strjoin(getenv("USER"), "@hiroshell: ");
	ft_welcome_badge(&meta);
	//getname
	//print intro
	ft_free_shell(&meta);
}
