/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:49 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/21 16:05:34 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*j_str;
	size_t	i;
	size_t	k;

	if (!s1)
		return (s2);
	j_str = (char *) ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
			sizeof(char));
	if (!j_str)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[k])
		j_str[i++] = s1[k++];
	ft_free_null(&s1);
	k = 0;
	while (s2[k])
		j_str[i++] = s2[k++];
	ft_free_null(&s2);
	return (j_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	size_t	i;

	j_str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (j_str == NULL)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		j_str[i++] = *s1++;
	while (s2 && *s2)
		j_str[i++] = *s2++;
	j_str[i] = '\0';
	return (j_str);
}
