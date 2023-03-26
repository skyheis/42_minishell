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