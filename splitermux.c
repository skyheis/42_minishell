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

#include "include/minishell.h"
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

int	ft_strlen_pez(char *s, t_mish *meta)
{
	int	i;

	i = 0;
	while (s[meta->f] == 32)
		(meta->f)++;
	while (s[meta->f])
	{
		if (s[meta->f] == SQUT)
		{
			i++;
			(meta->f)++;
			while (s[meta->f] != SQUT)
			{
				i++;
				(meta->f)++;
			}
		}
		if (s[meta->f] == DQUT)
		{
			i++;
			(meta->f)++;
			while (s[meta->f] != DQUT)
			{
				i++;
				(meta->f)++;
			}
		}
		if (s[meta->f] == 32)
			break ;
		i++;
		(meta->f)++;
	}
	return (i);
}

char	**ft_splitermux(char *s, t_mish *meta)
{
	size_t	i;
	int		j;
	int		k;
	char	**new;

	j = 0;
	k = 0;
	i = 0;
	//meta->f = 0; // METTERE NEL CASO IN CUI TESTI splitermux.c da solo
	while (s[i] == 32)
		i++;
	new = (char **) ft_calloc (ft_strlen(s), sizeof(char *));
	new[0] = (char *) ft_calloc ((ft_strlen_pez(s, meta) + 1), sizeof(char));
	while (i < ft_strlen(s) && s[i] != '|')
	{
		while (s[i] == 32 && s[i])
			i++;
		while (s[i] && s[i] != '|')
		{
			while (s[i] != 39 && s[i] && s[i] != 34 && s[i] != 32)
				new[k][j++] = s[i++];
			if (s[i] == SQUT && s[i])
			{
				new[k][j++] = SQUT;
				i++;
				while (s[i] != SQUT && s[i])
					new[k][j++] = s[i++];
				if (s[i])
					new[k][j++] = SQUT;
			}
			if (s[i] == DQUT && s[i])
			{
				new[k][j++] = DQUT;
				i++;
				while (s[i] != DQUT && s[i])
					new[k][j++] = s[i++];
				if (s[i])
					new[k][j++] = DQUT;
			}
			if (s[i] == 32 || !s[i])
				break ;
			i++;
		}
		new[k][j] = '\0';
		k++;
		new[k] = (char *) ft_calloc ((ft_strlen_pez(s, meta) + 1), sizeof(char));
		j = 0;
		if (s[i] == '|')
			break ;
	}
	new[k] = NULL;
	if (s[i] == '|')
		meta->flag = 1;
	return (new);
}
/*
int		main()
{
	char **str;
	t_mish a;
	//str = ft_splitermux(" e ch\"a '  ' \" ciao   'a'", &a);
	//str = ft_splitermux(" e cha ' as ' ci 'ao", &a);
	//str = ft_splitermux("cia'o smasb ' ", &a);
	//str = ft_splitermux("ciao a' a\"", &a);
	//str = ft_splitermux(" a'cane ' ' ssss", &a); // CONTROLLARE
	//str = ft_splitermux(" \"ciao ", &a);
	//str = ft_splitermux(" \'ciao ", &a);
	//str = ft_splitermux("ciao\"$USERzzzzz'\"", &a); //con il ./minishell non stampa, qui stampa ok
	//str = ft_splitermux("ciao $USERs'", &a);
	int i = 0;

	while (str[i]) 
		printf("%s\n", str[i++]);
}
*/
