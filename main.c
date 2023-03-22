/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 19:47:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check dei free che ho gia fatto casino

int	ft_free_shell(t_mish *meta)
{
	ft_free((void **) &(meta->context));
	if (meta->fd_history > 0)
		close(meta->fd_history);
	rl_clear_history();
	return (1);
}

void	ft_clean_window(t_mish *meta)
{
	char *clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve(clean_path[0], clean_path, meta->env);
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

void	ft_set_history(t_mish *meta)
{
	char	*line;

	meta->path_history = ft_strjoin(getenv("HOME") , "/.minishell_history");
	meta->fd_history = open(meta->path_history,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	line = get_next_line(meta->fd_history);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		ft_free((void **)&line);
		line = get_next_line(meta->fd_history);
	}
}

void	ft_fill_history(t_mish *meta)
{
	add_history(meta->line);
	ft_putstr_fd(meta->line, meta->fd_history);
	ft_putstr_fd("\n", meta->fd_history);
}

void	ft_history(t_mish *meta)
{
	int	i;
	char	*hline;

	i = 1;
	close(meta->fd_history);
	meta->fd_history = open(meta->path_history,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	hline = get_next_line(meta->fd_history);
	while (hline)
	{
		printf(" %4i %s", i, hline);
		i++;
		ft_free((void **)&hline);
		hline = get_next_line(meta->fd_history);
	}
}

void	ft_reset_line(t_mish *meta)
{
	ft_free((void **) &(meta->line));
}

int	main(int ac, char **av, char **envp)
{
	t_mish	meta;
	(void) ac;
	(void) av;
	(void) envp;

	meta.context = ft_strjoin(getenv("USER"), "@hiroshell: ");
	meta.env = envp;
	meta.line = NULL;
	meta.fd_history = 0;
	ft_welcome_badge(&meta);
	ft_set_history(&meta);
	while (1)
	{
		meta.line = readline(meta.context);
		// tutta questa parte va fatta dopo, con molti piu check.
		// farei gia' tutto in matrice, quindi line viene sistemata contando
		// '' "" e $, poi splitti tutto con ft_split tipo
		if (!ft_strncmp(meta.line, "history", 5))
			ft_history(&meta);
		else if (!ft_strncmp(meta.line, "quit", 5))
			break ;
		else
			printf("daje!\n");
		ft_fill_history(&meta);
		//readline va freeata?
		ft_reset_line(&meta);
	}
	//getname
	//print intro
	ft_free_shell(&meta);
}
