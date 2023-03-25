/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:16:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/25 16:47:28 by ggiannit         ###   ########.fr       */
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

typedef struct	s_exenv
{
	char			*key;
	char			*value;
	struct s_exenv	*next;
}				t_exenv;

typedef struct	s_mish
{
	char	*line;
	char	*user;
	char	*context;
	char	*abs_path; // per cd e pwd
	int		fd_history;
	char	*path_history;
	int		exit_code;
	int		f;
	char	**env;
	int		flag; //handle_realine/split + 
	t_cmd	*cmd;
}				t_mish;


void	ft_printnodes(t_cmd *cmd, t_mish *meta);



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

/* parse_line */
char	*ft_linejoin(char *line, char *piece, int n);
char	*ft_env_value(char	*line_key, char **env);
char	*ft_parse_word(char *line, t_mish *meta);

/* handle_realine */
void	ft_handle_line(t_mish *meta);

/* ft_splitermux */
char	**ft_splitermux(char *s, t_mish *meta);

/* env_list */

#endif
