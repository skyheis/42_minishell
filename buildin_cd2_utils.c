#include "minishell.h"

int	ft_cd_meno(t_mish *meta)
{
	char	*tmp;

	tmp = ft_strdup(meta->curdir);
	ft_free((void **) &(meta->curdir));
	meta->curdir = ft_strdup(meta->olddir);
	ft_free((void **) &(meta->olddir));
	meta->olddir = tmp;
	printf("%s\n", meta->curdir);
	chdir(meta->curdir);
	return (1);
}

int	ft_cd_slash(t_mish *meta, t_cmd *node)
{
	int	i;

	i = 0;
	if (node->pot[1][0] != '-')
	{
		ft_cd_slash2(meta, node);
		return (1);
	}
	if (node->pot[1][0] == '-' && (!node->pot[1][1] || node->pot[1][1] == 32))
		return (ft_cd_meno(meta));
	return (0);
}

void	ft_pre_slash_2(t_mish *meta, t_cmd *node, int i)
{
	while (node->pot[1][i])
	{
		if (node->pot[1][i] && (!ft_strncmp(&node->pot[1][i], "..", 2)
			|| (!ft_strncmp(&node->pot[1][i], "../", 3))))
		{
			ft_cd_pre(meta);
			chdir(meta->curdir);
			i += 3;
		}
		else if (node->pot[1][i] && ((ft_isalpha(node->pot[1][i])
			|| ft_isdigit(node->pot[1][i])) ||
				(!ft_strncmp(&node->pot[1][i], "./", 2)
					&& (ft_isalpha(node->pot[1][i + 2])
						|| ft_isdigit(node->pot[1][i + 2])))))
		{
			if (!ft_strncmp(&node->pot[1][i], "./", 2))
				i += 2;
			chdir(&node->pot[1][i]);
			ft_next_slash(meta, &node->pot[1][i]);
			i += len_slash(&node->pot[1][i]);
			i++;
		}
		else
			i++;
	}
}

static void	ft_cd_slash2_2_2(t_mish *meta, t_cmd *node, int *i)
{
	int	k;

	k = 0;
	if (!ft_strncmp(&node->pot[1][*i], "./", 2))
		*i += 2;
	ft_find_path(meta->home_path, &k);
	chdir(&meta->home_path[k]);
	ft_next_slash(meta, &node->pot[1][*i]);
	(*i) += len_slash(&node->pot[1][*i]);
	*i += 1;
}

void	ft_cd_slash2_2(t_mish *meta, t_cmd *node, int i, int k)
{
	while (node->pot[1][i])
	{
		k = 0;
		if (!ft_strncmp(&node->pot[1][i], "..", 2)
			|| (!ft_strncmp(&node->pot[1][i], "../", 3)))
		{
			ft_find_path(meta->home_path, &k);
			chdir(&meta->home_path[k]);
			ft_cd_pre(meta);
			i += 3;
		}
		else if ((ft_isalpha(node->pot[1][i]) || ft_isdigit(node->pot[1][i])) ||
			(!ft_strncmp(&node->pot[1][i], "./", 2)
				&& (ft_isalpha(node->pot[1][i + 2])
					|| ft_isdigit(node->pot[1][i + 2]))))
		{
			ft_cd_slash2_2_2(meta, node, &i);
		}
		else
			i++;
	}
}
