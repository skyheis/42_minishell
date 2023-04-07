/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/07 16:21:39 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check dei free che ho gia fatto casino
// The WIFEXITED and WEXITSTATUS macros are used to check whether the child process terminated normally and to retrieve its exit status, respectively.

void	ft_clean_for_file(char **env)
{
	char *clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve("/usr/bin/clear", clean_path, env);//, envp);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
}

void	ft_print_file(t_mish *meta, char *filename)
{
	int		fd;
	int		b_readed;
	char	*file_memory;
	char	*full_badge;

	(void) meta;
	//printf("\e[1;1H\e[2J");
	ft_clean_for_file(meta->env);
	fd = open(filename, O_RDONLY);
	b_readed = READ_SIZE;
	full_badge = NULL;
	if (fd == -1)
		return ;
	while (b_readed == READ_SIZE)
	{
		file_memory = (char *) ft_calloc(READ_SIZE + 1, sizeof(char));
		b_readed = read(fd, file_memory, READ_SIZE);
		if (b_readed == -1)
		{
			ft_free((void **) &(file_memory));
			return ;
		}
		full_badge = ft_strjoin_free(full_badge, file_memory);
	}
	close(fd);
	printf("%s", full_badge);
	// se serve, mettiamo full_badge in struct e free in free_shell
	ft_free((void **) &(full_badge));
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
	if (meta->line && meta->line[0])
	{
		add_history(meta->line);
		ft_putstr_fd(meta->line, meta->fd_history);
		ft_putstr_fd("\n", meta->fd_history);
	}
}

void	ft_reset_line(t_mish *meta)
{
	if (meta->infile != -2)
	{
		close(meta->infile);
		meta->infile = -2;
	}
	if (meta->outfile != -2)
	{
		close(meta->outfile);
		meta->outfile = -2;
	}
	if (access("/tmp/.heredoc", R_OK))
		unlink("/tmp/.heredoc");
	ft_free((void **) &(meta->line));
}

int	ft_free_shell(t_mish *meta)
{
	ft_cmdlst_clear(&(meta->cmd));
	ft_reset_line(meta);
	ft_free((void **) &(meta->context));
	if (meta->fd_history > 0)
		close(meta->fd_history);
	rl_clear_history();
	ft_free_matrix(&(meta->env));
	ft_envlst_clear(&(meta->ext_env));
	ft_free((void **) &(meta->path_history));
	return (1);
}

	// tutta questa parte va fatta dopo, con molti piu check.
	// farei gia' tutto in matrice, quindi line viene sistemata contando
	// '' "" e $, poi splitti tutto con ft_split tipo
int	main(int ac, char **av, char **envp)
{
	t_mish	meta;
	(void)	ac;
	(void)	av;
	(void)	envp;

	meta.context = ft_strjoin(getenv("USER"), "@duckshell: ");
	meta.env = ft_set_newenv(envp);
	meta.line = NULL;
	meta.fd_history = 0;
	meta.cmd = 0;
	meta.exit_code = 0;
	meta.abs_path = getenv("HOME");
	meta.ext_env = NULL;
	meta.c_stdin = dup(0);
	meta.c_stdout = dup(1);
	meta.infile = -2;
	meta.outfile = -2;
	ft_sign_ecode(&meta , 0);
	ft_pwd(&meta); //set current pwd-path to meta->abs_path

	//welcome
	ft_print_file(&meta, "badge/badge.bdg");
	printf("\nWelcome %s\n\n", getenv("USER"));

	ft_set_history(&meta);
	while (1)
	{
		signal(SIGQUIT, ft_sign_handler_rl); // ctrl-/
		signal(SIGINT, ft_sign_handler_rl); // ctrl-C
		meta.line = readline(meta.context);
		if (!meta.line)
			break ;
		ft_fill_history(&meta);
		ft_handle_line(&meta);
		//if (ft_handle_commands(&meta, meta.cmd))
		//	break ;
		//if (mini_pipe(&meta, meta.cmd, 1) == -1)
		meta.exit_code = ft_pipe_or_not(&meta, meta.cmd);
		printf("exit_code is: %i\n", meta.exit_code);
		if (meta.exit_code == -1)
			break ;
		//ft_cmdlst_clear(&(meta.cmd_head));
		//printf("\necode %i\n", meta.exit_code);
		ft_cmdlst_clear(&(meta.cmd));
		ft_reset_line(&meta);
	}
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
