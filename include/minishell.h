/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:16:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/17 15:15:27 by ggiannit         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**pot;
	char			**red;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_exenv
{
	char			*key;
	char			*value;
	struct s_exenv	*next;
}				t_exenv;

typedef struct s_mish
{
	char	*line;
	char	*user;
	char	*context;
	int		fd_history;
	char	*path_history;
	int		exit_code;
	int		pwd;
	char	*curdir;
	char	*olddir;
	char	*home_path;
	char	**env;
	int		flag;
	t_cmd	*cmd;
	t_cmd	*cmd_head;
	t_exenv	*ext_env;
	int		c_stdin;
	int		c_stdout;
	int		infile;
	int		outfile;
	char	*duckpath;
}				t_mish;

typedef struct s_spl
{
	size_t	i;
	int		j;
	int		k;
	int		f;
	char	**new;
}				t_spl;

typedef struct s_prs
{
	int		i;
	int		n;
	char	*value;
}				t_prs;

void	ft_printnodes(t_cmd *cmd, t_mish *meta);
int		ft_free_shell(t_mish *meta);
int		ft_duck(t_mish *meta);

/* cmd_list */
void	ft_cmdlst_iterstr(t_cmd *cmd, char *(*parse1)(char *, t_mish *),
			char *(*parse2)(char *, t_mish *), t_mish *meta);
void	ft_cmdlst_clear(t_cmd **cmd);
void	ft_cmdlst_addfront(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_cmdlst_new(char **pot);

/* parse_line */
char	*ft_linejoin(char *line, char *piece, int n);
char	*ft_env_value(char	*line_key, char **env, t_mish *meta, int i);
char	*ft_parse_word(char *line, t_mish *meta);
void	ft_parse_word_else_1(char **newline, t_prs *prs,
			t_mish *meta);
void	ft_parse_word_else_2(char *line, t_mish *meta,
			char **newline, t_prs *prs);
void	ft_parse_word_else_dquot(char *line, t_mish *meta,
			char **newline, t_prs *prs);
void	ft_parse_word_2_1(char *line, t_mish *meta,
			char **newline, t_prs *prs);
void	ft_parse_word_else_3(char *line, char **newline, t_prs *prs);
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

/* buildin_export */
void	ft_export(t_mish *meta, t_cmd *node);

/* handle commands*/
int		ft_handle_commands(t_mish *meta, t_cmd *node);
int		ft_pre_slash(t_mish *meta, t_cmd *node);
void	ft_cd_slash2(t_mish *meta, t_cmd *node);
void	ft_cd_pre(t_mish *meta);
void	ft_slash(t_mish *meta);
void	ft_next_slash(t_mish *meta, char *str);
int		len_slash(char *str);
void	ft_pre_slash_2(t_mish *meta, t_cmd *node, int i);
void	ft_cd_slash2_2(t_mish *meta, t_cmd *node, int i, int k);
void	ft_unset(t_mish *meta, t_cmd *node);
int		ft_cd_slash(t_mish *meta, t_cmd *node);
void	ft_abs_path(t_mish *meta);
void	ft_pwd(t_mish *meta);
int		ft_cd(t_mish *meta, t_cmd *node);

/* handle_setenv */
void	ft_handle_setenv(t_mish *meta, t_cmd *node);
int		ft_isasetenv(char *str);

/* env_list */
void	ft_envlst_clear(t_exenv **exenv);
void	ft_envlst_addfront(t_exenv **exenv, t_exenv *new);
t_exenv	*ft_envlst_new(char *str);
void	ft_envlst_nullnode(t_exenv *exenv, char *key);

/* custom_env */
char	**ft_matrixdel(char	**mat, char	*str);
char	**ft_matrixadd(char	**mat, char	*str);
char	**ft_replace_add_env(char **mat, char *str);
char	**ft_set_newenv(char **envp);

/* env utils */
int		ft_matrixlen(char **mat);
int		ft_findchar(char *str, char c);
int		ft_envlst_statusvalue(t_exenv *exenv, char *key);
char	*ft_envlst_retvalue(t_exenv *exenv, char *key);
void	ft_envlst_newvalue(t_exenv *exenv, char *key, char *str);

/* find_binary */
char	*ft_getenv(char *to_get, char **env);
char	*ft_getpath(char *full_path, t_mish *meta, t_cmd *node);
void	ft_getcmd(t_mish *meta, t_cmd *node);
int		ft_execbin(t_mish *meta, t_cmd *node);

/* free n history */
char	*ft_set_context(void);
void	ft_set_history(t_mish *meta);
void	ft_fill_history(t_mish *meta);
void	ft_reset_line(t_mish *meta);
int		ft_free_shell(t_mish *meta);

/* mini_pipe & utils*/
int		ft_mini_pipe(t_mish *meta, t_cmd *node, int fd_write);
int		ft_pipe_or_not(t_mish *meta, t_cmd *node);
int		ft_close_n_ret(int fd1, int fd2, int fd3, int ret_num);
void	ft_redirect(t_mish *meta, int fd_in, int fd_out);
void	ft_red_fromfile(t_mish *meta);
void	ft_rev_redirect(t_mish *meta);

/* redirect & utils*/
int		ft_do_red(t_mish *meta, t_cmd *node);
int		ft_red_error(t_mish *meta);
int		ft_in_heredoc(t_mish *meta, char *delimiter);
void	ft_parse_red_else_1(char *line, char **newline, t_prs *prs);
void	ft_parse_red_else_2(char *line, t_mish *meta,
			char **newline, t_prs *prs);
void	ft_parse_red_else_3(char *line, char **newline, t_prs *prs);

/* sign_handler */
void	ft_sign_ecode(t_mish *meta, int ecode);
int		ft_magic_heredoc(int keepit);
void	ft_sign_handler_heredoc(int sig);
void	ft_sign_handler_exec(int sig);
void	ft_sign_handler_rl(int sig);

/* ft_splitermux & utils */
char	**ft_splitermux(char *s, t_mish *meta);
int		ft_strmux_pez(char *s, int *f);
int		ft_count_word_mux(char *str);
int		ft_iscut(char c);

/* ft_splitered & utils*/
char	**ft_splitered(char *s, t_mish *meta);
int		ft_strred_pez(char *s, int *f);
int		ft_count_word_red(char *str);

/* print file */
void	ft_print_file(t_mish *meta, char *filename);

#endif
