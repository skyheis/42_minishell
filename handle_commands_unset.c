#include "minishell.h"

void	ft_set_env(t_mish *meta, char **tmp_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp_env[i])
	{
		while (tmp_env[i][j])
		{
			meta->env[i][j] = tmp_env[i][j];
			j++;
		}
		i++;
	}
}

void	ft_unset(t_mish *meta)
{
	int		i;
    int		j;
    char	**tmp_env;

	i = 0;
    j = 1;
	while (meta->env[i])
    {
        while (meta->cmd->pot[j] && !ft_strncmp(meta->env[i], meta->cmd->pot[j],
            ft_strlen(meta->cmd->pot[j])))
        {
			tmp_env = (char **) ft_calloc ((ft_matrixlen(meta->env) + 1), sizeof(char *));
			tmp_env = ft_set_newenv(meta->env, 1, meta, j);
			ft_free_matrix(&(meta->env));
			meta->env = (char **) ft_calloc (ft_matrixlen(tmp_env) + 1, sizeof(char *));
			ft_set_env(meta, tmp_env);
			ft_free_matrix(&(tmp_env));
			j++;
		}
		i++;
	}
}