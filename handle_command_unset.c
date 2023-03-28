#include "minishell.h"

void	ft_unset(t_mish *meta)
{
	int	i;

	i = 0;
	while (meta->env[i])
    {
        if (!ft_strncmp(meta->env[i], meta->cmd->pot[1],
            ft_strlen(meta->cmd->pot[1])))
        {
            
        }
    }
}