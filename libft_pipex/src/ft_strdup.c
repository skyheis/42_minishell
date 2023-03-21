/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:46:56 by ggiannit          #+#    #+#             */
/*   Updated: 2022/10/08 10:10:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	siz_s;

	siz_s = ft_strlen(s) + 1;
	t = (char *) malloc(siz_s * sizeof(char));
	if (t == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(t, s, siz_s);
	return (t);
}
