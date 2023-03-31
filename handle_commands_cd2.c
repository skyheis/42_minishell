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

void	ft_slash(t_mish *meta, int k, char *pot)
{
	char *cwd;

	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	cwd = (char *) ft_calloc (ft_strlen("PWD=")
		+ ft_strlen(pot) + 1, sizeof(char));
	cwd = ft_strjoin ("PWD=", pot);
	if (cwd[ft_strlen(cwd) - 1] == '/' && ft_isalpha_slash(&cwd[4]))
		cwd[ft_strlen(cwd) - 1] = '\0';
	free(meta->env[k]);
	meta->env[k] = (char *) ft_calloc(ft_strlen(cwd) + 1, sizeof(char));
	meta->env[k] = ft_strjoin(meta->env[k], cwd);
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
			tmp = (char *) ft_calloc (ft_strlen(meta->env[meta->pwd]) + 1, sizeof(char));
			tmp = ft_strjoin(tmp, meta->env[meta->pwd]);
			ft_replace_add_env(meta->env, ft_strjoin("PWD=", &meta->env[i][7]));
			printf("%s\n", &meta->env[meta->pwd][4]);
			ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &tmp[4]));
			free(tmp);
			break;
		}
		i++;
	}
	return (1);
}

int	ft_cd_slash(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->env[i] && meta->cmd->pot[1][0] != '-') // manca il /..////home/niccolo/Desktop DA FARE!!
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			if (meta->cmd->pot[1][1] && (meta->cmd->pot[1][1] == '.' ||
				meta->cmd->pot[1][1] == '/'))
				ft_slash(meta, i, "/");
			else
				ft_slash(meta, i, &meta->cmd->pot[1][0]);
			return (1);
		}
		i++;
	}
	if (meta->cmd->pot[1][0] == '-' && !meta->cmd->pot[1][1])
		return (ft_cd_meno(meta));
	return (0);
}

int	ft_pre_slash(t_mish *meta)
{
	int	i;
	int k;

	i = 0;
	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4]));
	ft_find_path(meta->abs_path, &i);
	chdir(&meta->abs_path[i]);
	ft_cd_pre(meta);
	i = 3;
	while (meta->cmd->pot[1][i])
	{
		if (!ft_strncmp(&meta->cmd->pot[1][i], "../", 3))
		{
			k = 0;
			ft_find_path(meta->abs_path, &k);
			chdir(&meta->abs_path[k]);
			ft_cd_pre(meta);
		}
		i += 3;
	}
	return (1);
}