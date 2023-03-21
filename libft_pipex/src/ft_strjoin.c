/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:49 by ggiannit          #+#    #+#             */
/*   Updated: 2022/11/07 22:01:31 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	j_str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (j_str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		j_str[i++] = *s1++;
	while (*s2)
		j_str[i++] = *s2++;
	j_str[i] = '\0';
	return (j_str);
}
