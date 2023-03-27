#include "minishell.h"

void	ft_slash(t_mish *meta, int k, char *pot)
{
	char *cwd;

	cwd = (char *) ft_calloc (ft_strlen("PWD=")
		+ ft_strlen(pot) + 1, sizeof(char));
	cwd = ft_strjoin ("PWD=", pot);
	free(meta->env[k]);
	meta->env[k] = (char *) ft_calloc(ft_strlen(cwd) + 1, sizeof(char));
	meta->env[k] = ft_strjoin(meta->env[k], cwd);
	free(cwd);
}

int	ft_cd_slash(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->env[i]) // manca il /..////home/niccolo/Desktop DA FARE!!
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
	return (0);
}