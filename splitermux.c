/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitermux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/24 19:08:06 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gestire < >

/*#include <stdio.h>
#include <stdlib.h>

#define SQUT 39
#define DQUT 34*/

int	ft_iscut(char c)
{
	if (c == 32)
		return (1);
	return (0);
}

int	ft_strlen_pez(char *s)
{
	static int	i;

	if (!s[i])
		i = 0;
	if (s[0] == 32)
		i++;
	while (s[i])
	{
		if (s[i] == SQUT)
		{
			i++;
			while (s[i] != SQUT)
				i++;
		}
		if (s[i] == DQUT)
		{
			i++;
			while (s[i] != DQUT)
				i++;
		}
		if (s[i] == 32)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i - 1);
}

char	**ft_splitermux(char *s, t_mish *meta)
{
	size_t	i;
	int		j;
	int		k;
	int		flag;
	char	**new;

	j = 0;
	flag = 0;
	k = 0;
	i = 0;
	if (s[i] == 32)
		i++;
	new = (char **) ft_calloc (ft_strlen(s) + 1, sizeof(char *));
	new[0] = (char *) ft_calloc (ft_strlen_pez(s) + 1, sizeof(char));
	while (i < ft_strlen(s) && s[i] != '|')
	{
		while (s[i] == 32)
			i++;
		while (s[i] && s[i] != '|')
		{
			if (s[i] == 34)
				flag = -42;
			else if (s[i] == 39)
				flag++;
			if ((ft_iscut(s[i]) && !flag) || (flag == 2 && ft_iscut(s[i]))
				|| (flag == -42 && ft_iscut(s[i]) && s[i - 1] == 34))
			{
				i++;
				break;
			}
			if (s[i])
				new[k][j++] = s[i];
			i++;
		}
		new[k][j] = '\0';
		k++;
		new[k] = (char *) ft_calloc (ft_strlen_pez(s) + 1, sizeof(char));
		flag = 0;
		j = 0;
		if (s[i] == '|')
			break ;
	}
	new[k] = NULL;
	if (s[i] == '|')
		meta->flag = 1;
	return (new);
}

/*int		main()
{
	char **str;

	//str = ft_splitermux(" e ch\"a '  ' \" ciao");
	//str = ft_splitermux(" e cha ' as ' ci 'ao");
	//str = ft_splitermux("cia'o smasb '");
	//str = ft_splitermux("ciao");
	//str = ft_splitermux(" a' cane ' ");
	//str = ft_splitermux(" \"ciao ");
	//str = ft_splitermux(" 'ciao ");
	str = ft_splitermux("ech'o' cas\"a '\" ");

	int i = 0;

	while (str[i]) 
		printf("%s\n", str[i++]);
}
*/
