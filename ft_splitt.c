/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/03/23 17:33:21 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	ft_strleny(const char *s)
{
	int	k;

	k = 0;
	if (!s)
		return (0);
	while (s[k] != '\0')
	{
		k++;
	}
	return (k);
}

int	ft_strlen_pez(char *s)
{
	static int	i;

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

char	**ft_splitermux(char *s)
{
	int		i;
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
	new = (char **) malloc (sizeof(char *) * (ft_strleny(s))); // al posto di strleny usa strlen
	new[0] = (char *) malloc (sizeof(char) * (ft_strlen_pez(s)));
	while (i < ft_strleny(s) && s[i] != '|')
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
		new[k] = (char *) malloc (sizeof(char) * (ft_strlen_pez(s)));
		flag = 0;
		j = 0;
	}
	return (new);
}

int		main()
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
