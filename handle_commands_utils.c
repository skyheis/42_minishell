#include "minishell.h"

void	ft_abs_path(t_mish *meta)
{
	int	i;
	int	k;

	i = -1;
	while (meta->env[++i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			//if (ft_strncmp(&meta->env[i][4], meta->abs_path,
				//ft_strlen(meta->abs_path)))
			//{
				k = 0;
				free(meta->env[i]);
				meta->env[i] = (char *) ft_calloc (ft_strlen(meta->abs_path) + 5,
					sizeof(char));
				ft_strlcpy(meta->env[i], "PWD=", 5);
				while (meta->abs_path[k])
				{
					meta->env[i][k + 4] = meta->abs_path[k];
					k++;
				}
			//}
		}
	}
}

void	ft_find_path(char *str, int *k)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '/')
			*k = j;
		j++;
	}
}