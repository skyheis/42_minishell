#include "minishell.h"

void	ft_abs_path(t_mish *meta)
{
	int	i;
	int	k;

	i = -1;
	ft_replace_add_env(meta->env, ft_strjoin("OLDPWD=", &meta->env[meta->pwd][4])); // freeare lo strjoin dentro ft_replace_add_env
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

int	ft_find_path(char *str, int *k)
{
	int	j;
	int	find_slash;

	j = 0;
	find_slash = 0;
	while (str[j])
	{
		if (str[j] == '/')
		{
			*k = j;
			find_slash++;
		}
		j++;
	}
	if (find_slash == 1)
		return (-42);
	return (0);
}

void	ft_tupadre(t_mish *meta, int ecode);

void	sign_handler(int sig)
{
	if (sig == SIGINT) // ctrl-C // deve dare nuova schermata
	{
		ft_tupadre(NULL, 130);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		
		rl_redisplay();
	}
}
