/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:53:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 18:43:00 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_error(t_mish *meta)
{
	ft_putstr_fd("duckshell:\
		syntax error near unexpected token `newline'\n", 2);
	meta->exit_code = 2;
	return (2);
}

void	ft_in_heredoc_child(t_mish *meta, char *delimiter)
{
	char	*nline;
	size_t	delimiter_size;

	meta->infile = open("/tmp/.heredoc", O_WRONLY | O_CREAT, 0644);
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
	get_next_line(-42);
	ft_free_null(&nline);
	ft_free_null(&delimiter);
	ft_free_shell(meta);
	exit(1);
}

int	ft_in_heredoc(t_mish *meta, char *delimiter)
{
	int	pid;

	ft_magic_heredoc(0);
	signal(SIGINT, ft_sign_handler_heredoc);
	unlink("/tmp/.heredoc");
	if (!delimiter[0])
		return (0);
	if (meta->infile != -2)
		close(meta->infile);
	pid = fork();
	ft_magic_heredoc(pid);
	if (!pid)
		ft_in_heredoc_child(meta, delimiter);
	waitpid(pid, &pid, 0);
	signal(SIGINT, ft_sign_handler_exec);
	if (!WEXITSTATUS(pid))
		return (0);
	meta->infile = open("/tmp/.heredoc", O_RDONLY);
	return (1);
}
