/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:16:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/31 10:38:59 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
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
	char	*abs_path; // per cd e pwd ---> e' il path principale
	int		fd_history;
	char	*path_history;
	int		exit_code;
	int		pwd;
	int		f;
	char	**env;
	int		flag; //handle_realine/split + 
	t_cmd	*cmd;
	t_cmd	*cmd_head;
	t_exenv	*ext_env;
	int		c_stdin;
	int		c_stdout;
}				t_mish;


void	ft_printnodes(t_cmd *cmd, t_mish *meta);
int		ft_free_shell(t_mish *meta);



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
int		ft_findchar(char *str, char c);

/* parse_line */
char	*ft_linejoin(char *line, char *piece, int n);
char	*ft_env_value(char	*line_key, char **env, t_mish *meta);
char	*ft_parse_word(char *line, t_mish *meta);

/* handle_realine */
void	ft_handle_line(t_mish *meta);
int		ft_find_path(char *str, int *k);
void	sign_handler(int sig);


/* ft_splitermux */
char	**ft_splitermux(char *s, t_mish *meta);

/* handle commands*/
int		ft_handle_commands(t_mish *meta, t_cmd *node);
int		ft_pre_slash(t_mish *meta);
void	ft_cd_pre(t_mish *meta);
void	ft_slash(t_mish *meta, int k, char *pot);
void	ft_unset(t_mish *meta, t_cmd *node);
int		ft_cd_slash(t_mish *meta);
void	ft_abs_path(t_mish *meta);
void	ft_pwd(t_mish *meta);
int		ft_cd(t_mish *meta);

/* handle_setenv */
void	ft_handle_setenv(t_mish *meta, t_cmd *node);
int		ft_isasetenv(char *str);

/* env_list */
char	*ft_envlst_retvalue(t_exenv *exenv, char *key);
void	ft_envlst_clear(t_exenv **exenv);
void	ft_envlst_addfront(t_exenv **exenv, t_exenv *new);
t_exenv	*ft_envlst_new(char *str);
void	ft_envlst_newvalue(t_exenv *exenv, char *key, char *str);

/* find_binary */
char	*ft_getenv(char *to_get, char **env);
char	*ft_getpath(char *full_path, t_mish *meta, t_cmd *node);
void	ft_getcmd(t_mish *meta, t_cmd *node);
int		ft_execbin(t_mish *meta, t_cmd *node);

/* mini_pipe */
int	mini_pipe(t_mish *meta, t_cmd *node, int fd_write);

#endif
