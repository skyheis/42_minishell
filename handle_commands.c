#include "minishell.h"

void	ft_echo(t_mish *meta)
{
	int	flag;
	int	i;

	i = 0;
	flag = ft_strncmp(meta->cmd->pot[1], "-n\0", 3);
	if (!meta->cmd->pot[1])
	{
		printf("\n");
		return ;
	}
	else if (flag)
		printf("%s ", meta->cmd->pot[1]);
	i = 2;
	while (meta->cmd->pot[i])
	{
		if (!flag && !meta->cmd->pot[i + 1])
			printf("%s", meta->cmd->pot[i]);
		else
			printf("%s ", meta->cmd->pot[i]);
		i += 1;
	}
	if (flag)
		printf("\n");
}

void	ft_pwd(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->cmd && meta->cmd->pot[1])
		meta->cmd->pot++;
	while (meta->env[i])
	{
		if (!ft_strncmp(meta->env[i], "PWD", 3))
		{
			if (!ft_strncmp(meta->line, "pwd", 3))
				printf("%s\n", &meta->env[i][4]);
			else
			{
				meta->abs_path = ft_calloc (ft_strlen(meta->env[i]) + 1, sizeof(char));
				meta->abs_path = ft_strjoin(meta->abs_path, meta->env[i]);
			}
			break ;
		}
		i++;
	}
}

void	ft_history(t_mish *meta)
{
	int	i;
	char	*hline;

	i = 1;
	close(meta->fd_history);
	meta->fd_history = open(meta->path_history,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	hline = get_next_line(meta->fd_history);
	while (hline)
	{
		printf("%4i %s", i, hline);
		i++;
		ft_free((void **)&hline);
		hline = get_next_line(meta->fd_history);
	}
}

void	ft_env(t_mish *meta)
{
	int	i;

	i = 0;
	if (meta->cmd->pot[1])
		return ;
	while (meta->env[i])
		printf("%s\n", meta->env[i++]);
}

int	ft_handle_commands(t_mish *meta)
{
	int	i;

	while (meta->cmd)
	{
		i = 0;
		while (meta->cmd->pot[i])
		{
			if (!ft_strncmp(meta->cmd->pot[i], "history", 8))
				ft_history(meta);
			else if (!ft_strncmp(meta->cmd->pot[i], "quit", 5) //quit c'e' da fare?
				|| !ft_strncmp(meta->cmd->pot[i], "exit", 5))
				return (1);
			else if (!ft_strncmp(meta->cmd->pot[i], "echo", 5))// caricare nuove envp ogni volta che cambio cartella  DA FARE!!
			{
				ft_echo(meta);
				break ;
			}
			else if (!ft_strncmp(meta->cmd->pot[i], "unset", 5))
			{
				ft_unset(meta);
				break;
			}
			else if (!ft_strncmp(meta->cmd->pot[i], "pwd", 4))
				ft_pwd(meta);
			else if (!ft_strncmp(meta->cmd->pot[i], "env", 4))
				ft_env(meta);
			else if (!ft_strncmp(meta->cmd->pot[i], "cd", 3))
			{
				ft_cd(meta);
				break ;
			}
			else
				printf("daje!\n");
			i++;
		}
		meta->cmd = meta->cmd->next;
	}
	return (0);
}