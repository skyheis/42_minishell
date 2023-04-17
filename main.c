/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:15:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/17 21:49:52 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_duckshell(t_mish *meta, char **envp)
{
	meta->context = ft_set_context();
	meta->curdir = ft_strdup(getenv("PWD"));
	if (getenv("OLDPWD"))
		meta->olddir = ft_strdup(getenv("OLDPWD"));
	else
		meta->olddir = ft_strdup(getenv("PWD"));
	meta->env = ft_set_newenv(envp);
	meta->line = NULL;
	meta->fd_history = 0;
	meta->cmd = 0;
	meta->exit_code = 0;
	meta->home_path = getenv("HOME");
	meta->ext_env = NULL;
	meta->c_stdin = dup(0);
	meta->c_stdout = dup(1);
	meta->infile = -2;
	meta->outfile = -2;
	meta->duckpath = getenv("PWD");
	ft_sign_ecode(meta, 0);
	write(1, "\033[0;97m", 7);
	ft_print_file(meta, "badge/badge.bdg");
	printf("\nWelcome %s\n\n", getenv("USER"));
	ft_set_history(meta);
}

int	ft_is_only_pipe(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->line[i] == 32)
		i++;
	if (meta->line[i] == '|')
	{
		ft_putstr_fd("duckshell: syntax error near unexpected token `|'\n", 2);
		meta->exit_code = 2;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_mish	meta;

	(void) ac;
	(void) av;
	ft_init_duckshell(&meta, envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_sign_handler_rl);
		meta.line = readline(meta.context);
		if (!meta.line)
			break ;
		ft_fill_history(&meta);
		if (!ft_is_only_pipe(&meta))
		{
			ft_handle_line(&meta);
			meta.exit_code = ft_pipe_or_not(&meta, meta.cmd);
			if (meta.exit_code == -1)
				break ;
		}
		ft_cmdlst_clear(&(meta.cmd));
		ft_reset_line(&meta);
	}
	ft_free_shell(&meta);
}

/*printf("exit_code is: %i\n", meta.exit_code);*/
