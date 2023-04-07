/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:16:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/07 17:36:40 by ggiannit         ###   ########.fr       */
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
# include <sys/time.h>
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
	char			**red;
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
	int		infile;
	int		outfile;
}				t_mish;


void	ft_printnodes(t_cmd *cmd, t_mish *meta);
int		ft_free_shell(t_mish *meta);
void	ft_print_file(t_mish *meta, char *filename);
int	ft_duck(t_mish *meta);


/* cmd_list */
void	ft_cmdlst_iterstr(t_cmd *cmd, char *(*parse1)(char *, t_mish *),
		char *(*parse2)(char *, t_mish *), t_mish *meta);
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
char	*ft_parse_red(char *line, t_mish *meta);

/* handle_readline */
void	ft_handle_line(t_mish *meta);
int		ft_find_path(char *str, int *k);
void	sign_handler(int sig);

/* buildin */
void	ft_echo(t_mish *meta, t_cmd *node);
void	ft_pwd(t_mish *meta);
void	ft_history(t_mish *meta, t_cmd *node);
void	ft_env(t_mish *meta, t_cmd *node);
void	ft_unset(t_mish *meta, t_cmd *node);

/* ft_splitermux */
char	**ft_splitermux(char *s, t_mish *meta);
/* ft_splitered */
char	**ft_splitered(char *s, t_mish *meta);

/* handle commands*/
int		ft_handle_commands(t_mish *meta, t_cmd *node);
int		ft_pre_slash(t_mish *meta, t_cmd *node);
void	ft_cd_slash2(t_mish *meta, t_cmd *node, int k);
void	ft_cd_pre(t_mish *meta);
void	ft_slash(t_mish *meta, int k, char *pot);
void	ft_unset(t_mish *meta, t_cmd *node);
int		ft_cd_slash(t_mish *meta, t_cmd *node);
void	ft_abs_path(t_mish *meta);
void	ft_pwd(t_mish *meta);
int		ft_cd(t_mish *meta, t_cmd *node);

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
int		ft_mini_pipe(t_mish *meta, t_cmd *node, int fd_write);
int		ft_pipe_or_not(t_mish *meta, t_cmd *node);

/* sign_handler */
void	ft_sign_ecode(t_mish *meta, int ecode);
int		ft_magic_heredoc(int keepit);
void	ft_sign_handler_heredoc(int sig);
void	ft_sign_handler_exec(int sig);
void	ft_sign_handler_rl(int sig);

/* redirect */
int	ft_do_red(t_mish *meta, t_cmd *node);

#endif
