/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:16:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/24 12:04:17 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ_SIZE 420

# define SQUT 39
# define DQUT 34

// la home con il / e' stata usata una volta, se viene riusata
// conveniene metterla nella struct?

typedef struct	s_cmd
{
	char			**pot; //matrix of line no pipe ([0] is command)
	struct s_cmd	*next; //ogni nodo un pipe :D
}				t_cmd;

typedef struct	s_mish
{
	char	*line;
	char	*user;
	char	*context;
	char	*abs_path; // per cd e pwd
	int		fd_history;
	char	*path_history;
	int		exit_code;
	char	**env;
	t_cmd	*cmd;
}				t_mish;

/* cmd_list */
void	ft_cmdlst_iterstr(t_cmd *cmd,
		char *(*parse)(char *, t_mish *), t_mish *meta);
void	ft_cmdlst_clear(t_cmd **cmd);
void	ft_cmdlst_addfront(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_cmdlst_new(char **pot);

/* custom_env */
int		ft_matrixlen(char **mat);
char	**ft_matrixdel(char	**mat, char	*str);
char	**ft_matrixadd(char	**mat, char	*str);
char	**ft_replace_add_env(char **mat, char *str);
char	**ft_set_newenv(char **envp);

#endif
