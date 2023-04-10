#include "minishell.h"

int	ft_isalpha_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_slash(t_mish *meta, int k, char *pot)// k da levare forse
{
	char *cwd;

	k = 0;
	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	cwd = (char *) ft_calloc (ft_strlen("PWD=")
		+ ft_strlen(pot) + 1, sizeof(char));
	cwd = ft_strjoin ("PWD=", pot);
	if (cwd[ft_strlen(cwd) - 1] == '/' && ft_isalpha_slash(&cwd[4]))
		cwd[ft_strlen(cwd) - 1] = '\0';
	free(meta->env[meta->pwd]);
	meta->env[meta->pwd] = (char *) ft_calloc(ft_strlen(cwd) + 1, sizeof(char));
	meta->env[meta->pwd] = ft_strjoin(meta->env[meta->pwd], cwd);
	free(cwd);
}

int	ft_cd_meno(t_mish *meta)
{
	int		i;
	char	*tmp;

	i = 0;
	while (meta->env[i])
	{
		if (!strncmp(meta->env[i], "OLDPWD=", 7))
		{
			tmp = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
			tmp = ft_strjoin(tmp, meta->env[meta->pwd]);
			ft_replace_add_env(meta->env, ft_strjoin("PWD=", &meta->env[i][7]));
			printf("%s\n", &meta->env[meta->pwd][4]);
			ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &tmp[4]));
			free(tmp);
			chdir(&meta->env[meta->pwd][4]);
			break ;
		}
		i++;
	}
	return (1);
}

int	ft_cd_slash(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 0;
	while (meta->env[i] && node->pot[1][0] != '-')
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			ft_cd_slash2(meta, node, i);
			return (1);
		}
		i++;
	}
	if (node->pot[1][0] == '-' && (!node->pot[1][1] || node->pot[1][1] == 32))
		return (ft_cd_meno(meta));
	return (0);
}

void	ft_next_slash(t_mish *meta, char *str)
{
	int		i;
	int		j;
	int		k;
	char	*cwd = NULL;

	i = -1;
	j = 0;
	k = 0;
	while (meta->env[++i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[i][4]));
			cwd = (char *) ft_calloc (ft_strlen(meta->env[i]), sizeof(char));
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (ft_strlen(cwd)
				+ ft_strlen(str) + 1, sizeof(char));
			if (cwd[5] != '\0')
				meta->env[i][j++] = '/';
			while(str[k] && str[k] != '/')
				meta->env[i][j++] = str[k++];
			//printf("%i\n", ft_strlen(str));
			meta->env[i] = ft_strjoin (cwd, meta->env[i]);
			break ;
		}
	}
	ft_free((void **)&cwd);
}

int	len_slash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (i);
		i++;
	}
	return (i);
}

int	ft_pre_slash(t_mish *meta, t_cmd *node)
{
	int	i;
	//int k;

	i = 0;
	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	if (!ft_strncmp(&node->pot[1][i], "..", 2)
		|| !ft_strncmp(&node->pot[1][i], "../", 3))
	{
		//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
		ft_find_path(meta->abs_path, &i);
		chdir(&meta->abs_path[i]);
		ft_cd_pre(meta);
		i = 3;
	}
	while (node->pot[1][i])
	{
		if (node->pot[1][i] && (!ft_strncmp(&node->pot[1][i], "..", 2) || (!ft_strncmp(&node->pot[1][i], "../", 3))))
		{
			//k = 0;
			//ft_find_path(meta->abs_path, &k);
			//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
			ft_cd_pre(meta);
			chdir(&meta->env[meta->pwd][4]);
			i += 3;
		}
		else if (node->pot[1][i] && ((ft_isalpha(node->pot[1][i]) || ft_isdigit(node->pot[1][i])) ||
			(!ft_strncmp(&node->pot[1][i], "./", 2) && (ft_isalpha(node->pot[1][i + 2])
				|| ft_isdigit(node->pot[1][i + 2])))))
		{
			//k = 0;
			if (!ft_strncmp(&node->pot[1][i], "./", 2))
				i += 2;
			//ft_find_path(meta->abs_path, &k);
			//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
			chdir(&node->pot[1][i]);
			ft_next_slash(meta, &node->pot[1][i]);
			i += len_slash(&node->pot[1][i]);
			i++;
		}
		else
			i++;
	}
	return (1);
}

void	ft_cd_slash2(t_mish *meta, t_cmd *node, int k)
{
	int	i;

	i = 1;
	//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[k][4]));
	ft_slash(meta, i, "/");
	while (node->pot[1][i] && !ft_isalpha(node->pot[1][i])
		&& !ft_isdigit(node->pot[1][i]))
		i++;
	i--;
	while (node->pot[1][i])
	{
		if (!ft_strncmp(&node->pot[1][i], "..", 2) || (!ft_strncmp(&node->pot[1][i], "../", 3)))
		{
			k = 0;
			ft_find_path(meta->abs_path, &k);
			chdir(&meta->abs_path[k]);
			//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
			ft_cd_pre(meta);
			i += 3;
		}
		else if ((ft_isalpha(node->pot[1][i]) || ft_isdigit(node->pot[1][i])) ||
			(!ft_strncmp(&node->pot[1][i], "./", 2) && (ft_isalpha(node->pot[1][i + 2])
				|| ft_isdigit(node->pot[1][i + 2]))))
		{
			k = 0;
			if (!ft_strncmp(&node->pot[1][i], "./", 2))
				i += 2;
			ft_find_path(meta->abs_path, &k);
			chdir(&meta->abs_path[k]);
			//ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
			ft_next_slash(meta, &node->pot[1][i]);
			i += len_slash(&node->pot[1][i]);
			i++;
		}
		else
			i++;
	}
	return ;
}
