/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:39:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/05 12:25:05 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_fd_in_error(char **av)
{
	int		is_here;
	char	*file;

	is_here = ft_strncmp("here_doc", av[1], 9);
	if (!is_here)
		file = av[2];
	else
		file = av[1];
	ft_putstr_fd("ggianit: no such file or directory: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (ret_num == -2)
		return (0);
	return (ret_num);
}

void	ft_redirect(int fd_in, int fd_out, int pp_close)
{
	if (fd_in != -1)
		dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
	if (pp_close != -1)
		close(pp_close);
}
