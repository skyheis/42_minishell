/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:27:27 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/17 15:32:51 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_set_context(void)
{
	char	*tmp;
	char	*context;

	tmp = ft_strjoin(getenv("USER"), "🦆duckshell: \033[0;39m");
	context = ft_strjoin("\033[0;97m", tmp);
	ft_free((void **) &tmp);
	return (context);
}

void	ft_set_history(t_mish *meta)
{
	char	*line;

	meta->path_history = ft_strjoin(getenv("HOME"), "/.minishell_history");
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
	if (meta->infile != -2 && meta->infile != -1)
	{
		close(meta->infile);
		meta->infile = -2;
	}
	if (meta->outfile != -2 && meta->outfile != -1)
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
	ft_free((void **) &(meta->curdir));
	ft_free((void **) &(meta->olddir));
	if (meta->fd_history > 0)
		close(meta->fd_history);
	rl_clear_history();
	ft_free_matrix(&(meta->env));
	ft_envlst_clear(&(meta->ext_env));
	ft_free((void **) &(meta->path_history));
	return (1);
}
