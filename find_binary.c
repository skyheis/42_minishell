/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:24:53 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/30 18:04:17 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *to_get, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(to_get);
	while (env[i])
	{
		if (!ft_strncmp(to_get, env[i], len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	return (&env[i][len + 1]);
}

char	*ft_getpath(char *full_path, t_mish *meta, t_cmd *node)
{
	int		i;
	char	**path_mat;
	char	*exec_path;

	(void) meta;
	i = 0;
	if (!access(node->pot[0], X_OK))
		return(NULL);
	path_mat = ft_split(full_path, ':');
	while (path_mat[i])
	{
		full_path = ft_strjoin("/", node->pot[0]);
		exec_path = ft_strjoin(path_mat[i], full_path);
		ft_free_null(&full_path);
		if (!access(exec_path, X_OK))
			break ;
		ft_free_null(&exec_path);
		i++;
	}
	if (!path_mat[i])
		exec_path = ft_strjoin("/bin/", node->pot[0]);
	ft_free_matrix(&path_mat);
	return (exec_path);
}

void	ft_getcmd(t_mish *meta, t_cmd *node)
{
	char	*full_path;

	full_path = ft_getenv("PATH", meta->env);
	full_path = ft_getpath(full_path, meta, node);
	if (full_path)
	{
		ft_free((void **) &(node->pot[0]));
		node->pot[0] = full_path;
	}
}

int	ft_endpath(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str && --i)
	{
		if (str[i] == '/')
			return (i + 1);
	}
	return (0);
}

int	ft_execbin(t_mish *meta, t_cmd *node)
{
	int	pid;

	ft_getcmd(meta, node);
	pid = fork();
	if (!pid)
	{
		execve(node->pot[0], node->pot, meta->env); //exit code
		if (WEXITSTATUS(EXIT_FAILURE) != 1)
		{
			printf("%s: command not found\n",
					&node->pot[0][ft_endpath(node->pot[0])]);
			ft_free_shell(meta);
			exit(127);
		}
		perror(&node->pot[0][ft_endpath(node->pot[0])]);
		ft_free_shell(meta);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &meta->exit_code, 0);
	//printf("\nexit_code %i\n\n", WEXITSTATUS(meta->exit_code));
	return (WEXITSTATUS(meta->exit_code));
}
