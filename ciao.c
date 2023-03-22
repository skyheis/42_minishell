#include "minishell.h"

void	ft_clean_window(char **envp)
{
	char *clean_path[2];

	clean_path[0] = ft_strjoin(NULL, "/usr/bin/clear");
	clean_path[1] = NULL;
	if (!clean_path[0])
		return ;
	if (!fork())
	{
		execve("/usr/bin/clear", clean_path, envp);
		exit(1);
	}
	wait(NULL);
	ft_free_null(clean_path);
}

int main(int ac, char **av, char **envp)
{
	ft_clean_window(envp);
}

