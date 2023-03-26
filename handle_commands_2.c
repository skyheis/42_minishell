#include "minishell.h"

void	ft_abs_path(t_mish *meta)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			//if (ft_strncmp(meta->env[i], meta->abs_path, ft_strlen(meta->abs_path)))
			//{
				free(meta->env[i]);
				meta->env[i] = (char *) ft_calloc (ft_strlen(meta->abs_path) + 1, sizeof(char));
				while (meta->abs_path[k])
				{
					meta->env[i][k] = meta->abs_path[k];
					k++;
				}
			//}
			return  ;
		}
		i++;
	}
}

void	ft_cd_core(t_mish *meta)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = 0;
	j = 0;
	k = 0;
	cwd = 0;
	if (!ft_strncmp(meta->cmd->pot[1], "../", 3))
		chdir("../");
	else
		chdir(meta->cmd->pot[1]);
	cwd = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (ft_strlen(meta->env[i]) + ft_strlen(meta->cmd->pot[1]) + 1, sizeof(char));
			meta->env[i][j] = '/';
			while(meta->cmd->pot[1][k])
				meta->env[i][++j] = meta->cmd->pot[1][k++];
			meta->env[i] = ft_strjoin (cwd, meta->env[i]);
			break ; //ft_getenv
		}
		i++;
	}
	free(cwd);
}

int	ft_cd2(t_mish *meta)
{
	int	i;

	i = 3;
	if (!ft_strncmp(meta->cmd->pot[1], "../", 3)) // ../ option with ../////// check
	{
		while (meta->cmd->pot[1][i])
		{
			if (meta->cmd->pot[1][i++] != '/')
				return (1);
		}
		chdir("../");
		//chiamo la funzione core
	}
	else
	{
		chdir(meta->cmd->pot[1]);
		//chiamo la funzione core
		return (0);
	}
}

int	ft_cd(t_mish *meta)
{
	if (!meta->cmd->pot[1]) // absolute path
	{
		chdir(&meta->abs_path[4]);
		ft_abs_path(meta);
		return (0);
	}
	else if (chdir(meta->cmd->pot[1]) != 0) // no path available
	{
		perror("Error");
		return (1);
	}
	else
	{
		if (ft_cd2(meta))
			return (1);
	}
	return (0);
}