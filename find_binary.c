/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:24:53 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/30 12:00:17 by ggiannit         ###   ########.fr       */
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

char	*ft_getpath(char *full_path, t_mish *meta)
{
	int		i;
	char	**path_mat;
	char	*exec_path;

	i = 0;
	if (!access(meta->cmd->pot[0], X_OK))
		return(NULL);
	path_mat = ft_split(full_path, ':');
	while (path_mat[i])
	{
		full_path = ft_strjoin("/", meta->cmd->pot[0]);
		exec_path = ft_strjoin(path_mat[i], full_path);
		ft_free_null(&full_path);
		if (!access(exec_path, X_OK))
			break ;
		ft_free_null(&exec_path);
		i++;
	}
	if (!path_mat[i])
		exec_path = ft_strjoin("/bin/", meta->cmd->pot[0]);
	ft_free_matrix(&path_mat);
	return (exec_path);
}

void	ft_getcmd(t_mish *meta)
{
	char	*full_path;

	full_path = ft_getenv("PATH", meta->env);
	full_path = ft_getpath(full_path, meta);
	if (full_path)
	{
		ft_free((void **) &(meta->cmd->pot[0]));
		meta->cmd->pot[0] = full_path;
	}
}

void	ft_execbin(t_mish *meta)
{
	ft_getcmd(meta);
	if (!fork())
	{
		execve(meta->cmd->pot[0], meta->cmd->pot, meta->env); //exit code
		exit(1);
	}
	wait(NULL);
}
