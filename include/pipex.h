/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:55:24 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/05 14:27:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

/* pipex_utils */
char	**ft_getcmd(char *cmd_str, char **envp);

/* handle_fd_utils */
int		ft_fd_in_error(char **av);
int		ft_pipez_check_acav(int ac, char **av);
int		ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num);
void	ft_redirect(int fd_in, int fd_out, int pp_close);

/* use_heredoc */
int		ft_get_heredoc(char *delimiter);

#endif
