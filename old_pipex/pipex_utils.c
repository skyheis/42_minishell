/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:21:29 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/04 10:43:19 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *to_get, char **envp)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(to_get);
		if (!ft_strncmp(to_get, envp[i], len) && envp[i][len] == '=')
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (&envp[i][len + 1]);
}

char	*ft_getpath(char *full_path, char *cmd)
{
	int		i;
	char	**path_mat;
	char	*exec_path;

	i = 0;
	if (!access(cmd, X_OK))
		return(NULL);
	path_mat = ft_split(full_path, ':');
	while (path_mat[i])
	{
		full_path = ft_strjoin("/", cmd);
		exec_path = ft_strjoin(path_mat[i], full_path);
		ft_free_null(&full_path);
		if (!access(exec_path, X_OK))
			break ;
		ft_free_null(&exec_path);
		i++;
	}
	if (!path_mat[i])
		exec_path = ft_strjoin("/bin/", cmd);
	ft_free_matrix(path_mat);
	return (exec_path);
}

char	**ft_getcmd(char *cmd_str, char **envp)
{
	char	**cmd_mat;
	char	*full_path;

	cmd_mat = ft_split(cmd_str, ' ');
	full_path = ft_getenv("PATH", envp);
	full_path = ft_getpath(full_path, cmd_mat[0]);
	if (full_path)
	{
		ft_free_null(&cmd_mat[0]);
		cmd_mat[0] = full_path;
	}
	return (cmd_mat);
}
