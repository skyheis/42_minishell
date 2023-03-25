#include "minishell.h"

void	ft_echo(t_mish *meta, int *i)
{
	if (!meta->cmd->pot[1])
	{
		printf("\n");
		return ;
	}
	else
		printf("%s ", meta->cmd->pot[1]);
	*i = 2;
	while (meta->cmd->pot[*i])
	{
		printf("%s ", meta->cmd->pot[*i]);
		*i += 1;
	}
	printf("\n");
}

//dobbiamo gestire i pwd
void	ft_pwd(t_mish *meta)
{
	(void) meta;
	printf("%s\n", getenv("PWD"));//ft_getenv
}

//bisogna chiamare la funzione free_all
void	ft_exit(t_mish *meta)
{
	(void) meta;
	if (meta->line[4] == 32 || meta->line[5] == '\0')
		exit (0);
}

void	ft_cd(t_mish *meta)
{
	char *cwd;

	if (chdir(meta->cmd->pot[1]) != 0)
    	perror("Error"); // se diverso da 0 mi vado a prendere l'absolute path cambiando directory con quello
	cwd = ft_strjoin(getenv("PWD"), "/");
	cwd = ft_strjoin(cwd, &meta->line[3]);
	//ft_replace_add_env(, );
	//printf("current working directory is: %s\n", cwd);
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
			else if (!ft_strncmp(meta->cmd->pot[i], "quit", 5))
				return (1);
			else if (!ft_strncmp(meta->cmd->pot[i], "echo", 5))
				ft_echo(meta, &i);
			else if (!ft_strncmp(meta->cmd->pot[i], "pwd", 4))
				ft_pwd(meta);
			else if (!ft_strncmp(meta->cmd->pot[i], "cd", 3))
				ft_cd(meta);
			else
				printf("daje!\n");
			i++;
		}
		meta->cmd = meta->cmd->next;
	}
	return (0);
}