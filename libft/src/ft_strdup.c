/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:46:56 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/22 16:54:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	return (newstr);
}
