/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:04:12 by ggiannit          #+#    #+#             */
/*   Updated: 2023/01/13 16:30:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*cmem;
	size_t	k;
	size_t	tot_size;

	k = 0;
	if (!nmemb || !size)
		return (NULL);
	tot_size = nmemb * size;
	cmem = (char *) malloc(tot_size);
	if (!cmem)
		return (NULL);
	while (k < tot_size)
		cmem[k++] = '\0';
	return (cmem);
}
