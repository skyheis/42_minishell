/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:04:12 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/12 15:20:04 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cmem;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	cmem = (void *) malloc(nmemb * size);
	if (cmem == NULL)
	{
		return (NULL);
	}
	ft_bzero(cmem, nmemb * size);
	return (cmem);
}
