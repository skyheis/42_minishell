#include "minishell.h"

void	ft_cd_next(t_mish *meta)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = -1;
	j = 0;
	k = 0;
	while (meta->env[++i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			cwd = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (ft_strlen(meta->env[i])
				+ ft_strlen(meta->cmd->pot[1]) + 1, sizeof(char));
			meta->env[i][j] = '/';
			while(meta->cmd->pot[1][k])
				meta->env[i][++j] = meta->cmd->pot[1][k++];
			meta->env[i] = ft_strjoin (cwd, meta->env[i]);
			break ;
		}
	}
	free(cwd);
}

void	ft_cd_pre(t_mish *meta)
{
	int		i;
	int		j;
	int		k;
	char	*cwd;

	i = 0;
	j = 0;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			ft_find_path(meta->env[i], &k);
			cwd = (char *) ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
			cwd = ft_strjoin (cwd, meta->env[i]);
			free(meta->env[i]);
			meta->env[i] = (char *) ft_calloc (k + 1, sizeof(char));
			j = -1;
			while (++j < k)
				meta->env[i][j] = cwd[j];
			break ;
		}
		i++;
	}
	free(cwd);
}

int	ft_cd2(t_mish *meta)
{
	int	i;

	i = 2;
	if (!ft_strncmp(meta->cmd->pot[1], "..", 2)) // ../ option with ../////// check
	{
		while (meta->cmd->pot[1][i])
		{
			if (meta->cmd->pot[1][i++] != '/')
				return (1);
		}
		i = 0;
		ft_find_path(meta->abs_path, &i);
		chdir(&meta->abs_path[i]);
		ft_cd_pre(meta);
	}
	else
	{
		chdir(meta->cmd->pot[1]);
		ft_cd_next(meta);
		return (0);
	}
	return (0);
}

int	ft_check_error_cd(t_mish *meta)
{
	int	i;

	i = 1;
	if (!ft_strncmp(meta->cmd->pot[1], "./", 2)) // . option or ./ option with ./////// check
	{
		while (meta->cmd->pot[1][i])
		{
			if (meta->cmd->pot[1][i] != '/')
				return (1) ;
			i++;
		}
		return (1);
	}
	else if (meta->cmd->pot[1][0] == '.')
	{
		if (meta->cmd->pot[1][1] != '.')
			return (1);
	}
	return (0);
}

int	ft_cd(t_mish *meta) // handleare il caso in cui ci sia solo cd / o cd // o cd /.
{
	if (!meta->cmd->pot[1]) // absolute path
	{
		chdir(&meta->abs_path[4]);
		ft_abs_path(meta);
		return (0);
	}
	else if (chdir(meta->cmd->pot[1]) != 0) // no path available
	{
		perror("Errory");
		return (1);
	}
	else
	{
		if (ft_check_error_cd(meta))
			return (1);
		if (ft_cd2(meta))
			return (1);
	}
	return (0);
}