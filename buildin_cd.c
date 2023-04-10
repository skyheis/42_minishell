#include "minishell.h"

/*void	ft_cd_next(t_mish *meta)
{
	int		i;
	int		j;
	int		k;
	char	*cwd = NULL;

	i = -1;
	j = 0;
	k = 0;
	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	while (meta->env[++i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			cwd = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (ft_strlen(cwd)
				+ ft_strlen(node->pot[1]) + 1, sizeof(char));
			if (cwd[5] != '\0')
				meta->env[i][j++] = '/';
			while(node->pot[1][k] && (node->pot[1][k] != '/'
				|| (node->pot[1][k + 1])))
				meta->env[i][j++] = node->pot[1][k++];
			meta->env[i] = ft_strjoin (cwd, meta->env[i]);
			break ;
		}
	}
	ft_free((void **)&cwd);
}
*/
void	ft_cd_pre(t_mish *meta)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = 0;
	j = 0;
	//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			k = 0;
			if (ft_find_path(meta->env[i], &k) == -42)
			{
				ft_slash(meta, i, "/");
				return ;
			}
			ft_find_path(meta->env[i], &k);
			cwd = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (k + 1, sizeof(char));
			j = -1;
			while (++j < k)
				meta->env[i][j] = cwd[j];
			free(cwd);
			break ;
		}
		i++;
	}
}

int	ft_cd2(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 2;
	if (!ft_strncmp(node->pot[1], "..", 2))
	{
		while (node->pot[1][i])
		{
			if (node->pot[1][i] && node->pot[1][i] != '/'
				&& (!ft_strncmp(&node->pot[1][i], "../", 3) ||
					node->pot[1][i] == '.'))
				return (ft_pre_slash(meta, node));
			else if (node->pot[1][i] && ((ft_isalpha(node->pot[1][i + 3]) || ft_isdigit(node->pot[1][i + 3])) ||
			(!ft_strncmp(&node->pot[1][i + 1], "./", 2) && (ft_isalpha(node->pot[1][i + 3])
				|| ft_isdigit(node->pot[1][i + 3])))))
				return (ft_pre_slash(meta, node));
			else if (node->pot[1][i] && node->pot[1][i] != '/')
				return (1);
			i++;
		}
		i = 0;
		ft_find_path(meta->abs_path, &i);
		chdir(&meta->abs_path[i]);
		ft_cd_pre(meta);
	}
	else
	{
		chdir(node->pot[1]);
		ft_pre_slash(meta, node); // ft_cd_next c'era prima
		return (0);
	}
	return (0);
}
/*
int	ft_check_error_cd(t_mish *meta, t_cmd *node)
{
	int	i;

	(void) meta;
	i = 1;
	if (!ft_strncmp(node->pot[1], "./", 2))
	{
		while (node->pot[1][i])
		{
			if (node->pot[1][i] != '/')
				return (1) ;
			i++;
		}
		return (1);
	}
	else if (node->pot[1][0] == '.')
	{
		if (node->pot[1][1] != '.')
			return (1);
	}
	return (0);
}
*/
int	ft_cd(t_mish *meta, t_cmd *node)
{
	if (!node->pot[1]) // absolute path
	{
		chdir(meta->abs_path);
		ft_abs_path(meta);
		return (0);
	}
	else if (node->pot[1][0] != '-' && chdir(node->pot[1]) != 0) // no path available
	{
		perror("Error");
		return (1);
	}
	else
	{
		if (node->pot[1][0] == '/' || node->pot[1][0] == '-')
		{
			if (ft_cd_slash(meta, node)) // controllo se /home e' presente in meta->env[i] senno' vado a cd2 e l'aggiungo
				return (1);
		}
		else if (ft_cd2(meta, node)) // prima era if senza else
			return (1);
	}
	return (0);
}
