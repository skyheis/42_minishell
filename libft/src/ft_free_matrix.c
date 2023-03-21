/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:19:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/31 15:59:14 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	if (!(*matrix))
		return (NULL);
	while ((*matrix)[i])
		ft_free_null(&(*matrix)[i++]);
	free(*matrix);
	return (NULL);
}

char	*ft_free_matrix_xy(char ***matrix, int x, int y)
{
	if (!*matrix)
		return (NULL);
	(void) x;
	while (y--)
	{
		ft_free_null((char **) &((*matrix)[y]));
	}
	free(*matrix);
	return (NULL);
}

/* for free gnl */
char	*ft_free_matrix_nomat(char **matrix, int i)
{
	while (i)
		ft_free_null(&(matrix)[i--]);
	return (NULL);
}
