/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:31:29 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/23 11:41:31 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tutte ritornano la nuova matrice e libera quella passata
 * quindi di usare tipo:
 *		envmat = ft_replace_add_env(envmat, "new=env");
 */

int	ft_matrixlen(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}

static int	ft_findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_matrixdel(char	**mat, char	*str)
{
	int		i;
	int		j;
	int		len;
	char	**newmat;

	len = ft_strlen(str);
	newmat = ft_calloc(ft_matrixlen(mat) + 1, sizeof(char *));
	if (!newmat)
		return (NULL);
	i = 0;
	j = 0;
	while (mat[i])
	{
		if (ft_strncmp(mat[i], str, len))
		{
			newmat[j] = ft_strdup(mat[i]);
			j++;
		}
		i++;
	}
	ft_free_matrix(&mat);
	return (newmat);
}

char	**ft_matrixadd(char	**mat, char	*str)
{
	int		i;
	int		j;
	char	**newmat;

	newmat = ft_calloc(ft_matrixlen(mat) + 2, sizeof(char *));
	if (!newmat)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		j = 0;
		newmat[i] = ft_calloc(ft_strlen(mat[i]) + 1, sizeof(char));
		while (mat[i][j])
		{
			newmat[i][j] = mat[i][j];
			j++;
		}
		i++;
	}
	newmat[i] = ft_strdup(str);
	ft_free_matrix(&mat);
	return (newmat);
}

char	**ft_replace_add_env(char **mat, char *str)
{
	int		i;
	char	*strcut;

	i = 0;
	strcut = ft_strdup(str);
	strcut[ft_findchar(str, '=')] = '\0';
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], strcut, ft_strlen(strcut)))
		{
			ft_free((void **) &(strcut));
			ft_free((void **) &(mat[i]));
			mat[i] = ft_strdup(str);
			return (mat);
		}
		i++;
	}
	ft_free((void **) &(strcut));
	return (ft_matrixadd(mat, str));
}

char	**ft_set_newenv(char **envp)
{
	int		i;
	int		j;
	char	**newenv;

	newenv = ft_calloc(ft_matrixlen(envp) + 1, sizeof(char *));
	if (!newenv)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		newenv[i] = ft_calloc(ft_strlen(envp[i]), sizeof(char));
		while (envp[i][j])
		{
			newenv[i][j] = envp[i][j];
			j++;
		}
		i++;
	}
	return (newenv);
}

/*int main(int ac, char **av, char **envp)
{
	char **lol = ft_set_newenv(envp);
	int i = -1;

	lol = ft_matrixadd(lol, "okok");
	lol = ft_matrixadd(lol, "POPIPOPI=00000000000000000000000");
	while (lol[++i])
		printf("%s\n", lol[i]);

	printf("\n\n\n");
	lol = ft_replace_add_env(lol, "POPIPOPIlol");
//	lol = ft_matrixdel(lol, "LESS");
//	lol = ft_matrixdel(lol, "LS_COLORS");
//	lol = ft_matrixdel(lol, "SHELL");
//	lol = ft_matrixdel(lol, "TERM");
//	lol = ft_matrixdel(lol, "PWD");
//	lol = ft_matrixdel(lol, "PATH");
	i = -1;
	while (lol[++i])
		printf("%s\n", lol[i]);
	ft_free_matrix(&lol);
	return 0;
}*/