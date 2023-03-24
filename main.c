/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/24 09:04:33 by ggiannit         ###   ########.fr       */
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
	ft_free((void **) &(meta->path_history));
	ft_free((void **) &(meta->path_history));
	return (1);
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
		{
			ft_free((void **) &(file_memory));
			return (0);
		}
		full_badge = ft_strjoin_free(full_badge, file_memory);
	}
	close(fd);
	printf("%s\nWelcome %s\n\n", full_badge, getenv("USER"));
	// se serve, mettiamo full_badge in struct e free in free_shell
	ft_free((void **) &(full_badge));
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
		//add_history(line);
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
	if (meta->line[6] == 'y' && (meta->line[7] == 32 || meta->line[7] == '\0'))
	{
		if (meta->line[7] == 32 && meta->line[8] != '\0')
			return ;
		close(meta->fd_history);
		meta->fd_history = open(meta->path_history,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		hline = get_next_line(meta->fd_history);
		while (hline)
		{
			printf("%4i %s", i, hline);
			i++;
			ft_free((void **)&hline);
			hline = get_next_line(meta->fd_history);
		}
	}
}

void	ft_reset_line(t_mish *meta)
{
	ft_free((void **) &(meta->line));
}

void	ft_echo(t_mish *meta)
{
	int	i;

	if (meta->line[4] == 32 && meta->line[5] == '-' && meta->line[6] == 'n'
		&& meta->line[7] == 32)
	{
		i = 8;
		while (meta->line[i])
			printf("%c", meta->line[i++]);
	}
	else if (meta->line[4] == 32)
	{
		i = 5;
		while (meta->line[i])
			printf("%c", meta->line[i++]);
		if (meta->line[5])
			printf("\n");
	}
}

//dobbiamo gestire i pwd
void	ft_pwd(t_mish *meta)
{
	if (meta->line[3] == 32)
		printf("%s\n", getenv("PWD"));
}

//bisogna chiamare la funzione free_all
void	ft_exit(t_mish *meta)
{
	if (meta->line[4] == 32 || meta->line[5] == '\0')
		exit (0);
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
		ft_fill_history(&meta);
		// tutta questa parte va fatta dopo, con molti piu check.
		// farei gia' tutto in matrice, quindi line viene sistemata contando
		// '' "" e $, poi splitti tutto con ft_split tipo
		if (!ft_strncmp(meta.line, "exit", 4))
			ft_exit(&meta);
		else if (!ft_strncmp(meta.line, "history", 7))
			ft_history(&meta);
		else if (!ft_strncmp(meta.line, "quit", 5))
			break ;
		else if (!ft_strncmp(meta.line, "pwd", 3))
			ft_pwd(&meta);
		else if (!ft_strncmp(meta.line, "echo", 4))
			ft_echo(&meta);
		else
			printf("daje!\n");
		//readline va freeata? --- >  Note that you must free the memory 
		//allocated by readline using the free function.
		ft_reset_line(&meta);
	}
	//getname
	//print intro
	ft_free_shell(&meta);
}

/* non serve, ma utilizzabile per altri casi
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
}*/
