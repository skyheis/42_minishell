/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:31:29 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 18:02:32 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tutte ritornano la nuova matrice e libera quella passata
 * quindi di usare tipo:
 *		envmat = ft_replace_add_env(envmat, "new=env");
 */

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

/* se str non e' dal nodocmd, ricordarsi di freeare */
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
	newmat[i] = str;
	ft_free_matrix(&mat);
	return (newmat);
}

/* se str non e' dal nodocmd, ricordarsi di freeare */
char	**ft_replace_add_env(char **mat, char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup(str);
	key[ft_findchar(str, '=')] = '\0';
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], key, ft_strlen(key))
			&& mat[i][ft_strlen(key)] == '=')
		{
			ft_free((void **) &(key));
			ft_free((void **) &(mat[i]));
			mat[i] = str;
			return (mat);
		}
		i++;
	}
	ft_free((void **) &(key));
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
		newenv[i] = ft_calloc(ft_strlen(envp[i]) + 2, sizeof(char));
		while (envp[i][j])
		{
			newenv[i][j] = envp[i][j];
			j++;
		}
		i++;
	}
	return (newenv);
}
