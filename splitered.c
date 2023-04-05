/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitered.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/05 18:16:02 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* split che ritorna una matrice con i soli redirect */

static int	ft_iscut(char c)
{
	if (!c || c == 32 || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	ft_strlen_pez(char *s, int *f)
{
	int	i;

	i = 5;
	while (s[*f] && s[*f] != '<' && s[*f] != '>')
	{
		if (s[*f] == SQUT)
		{
			*f += 1;
			while (s[*f] != SQUT)
				*f += 1;
		}
		if (s[*f] == DQUT)
		{
			*f += 1;
			while (s[*f] != DQUT)
				*f += 1;
		}
		*f += 1;
	}
	if ((s[*f] && s[*f] == '<') || (s[*f] && s[*f] == '>'))
	{
		if ((s[*f] == '<' && s[*f + 1] == '<') && (s[*f] == '>' && s[*f + 1] == '>'))
		{
			i++;
			*f += 1;
		}
		i++;
		*f += 1;
		while (s[*f] == 32)
			*f += 1;
		while (!ft_iscut(s[*f]))
		{
			if (s[*f] == SQUT)
			{
				i++;
				*f += 1;
				while (s[*f] != SQUT)
				{
					i++;
					*f += 1;
				}
			}
			if (s[*f] == DQUT)
			{
				i++;
				*f += 1;
				while (s[*f] != DQUT)
				{
					i++;
					*f += 1;
				}
			}
			i++;
			*f += 1;
		}
	}
/*	while (s[*f])
	{
		if (s[*f] == SQUT)
		{
			i++;
			*f += 1;
			while (s[*f] != SQUT)
			{
				i++;
				*f += 1;
			}
		}
		if (s[*f] == DQUT)
		{
			i++;
			*f += 1;
			while (s[*f] != DQUT)
			{
				i++;
				*f += 1;
			}
		}
		//if (s[*f] == 32)
		if (ft_iscut(s[*f]))
			break ;
		i++;
		*f += 1;
	}*/
	return (i);
}

static int	ft_count_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	if (!str)
		return (1);
	while (str && str[i])
	{
		while (str[i] && str[i] != '<' && str[i] != '>')
		{
			if (str[i] && str[i] == SQUT)
			{
				i++;
				while (str[i] && str[i] != SQUT)
					i++;
			}
			if (str[i] && str[i] == DQUT)
			{
				i++;
				while (str[i] && str[i] != DQUT)
					i++;
			}
			if (str[i] == '|')
				return (word) ;
			i++;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				i++;
		}
		word++;
	}
	return (word);
}

char	**ft_splitered(char *s, t_mish *meta)
{
	size_t	i;
	int		j;
	int		k;
	int		f;
	char	**new;

	k = 0;
	i = 0;
	f = i;
	//printf("word: %i\n", ft_count_word(s));
	new = (char **) ft_calloc (ft_count_word(s) + 1, sizeof(char *));
	while (s[i] && s[i] != '|')
	{
		j = 0;
		/*int test = 0;
		test = (ft_strlen_pez(s, &f) + 1);
		new[k] = ft_calloc (test, sizeof(char));*/
		new[k] = ft_calloc ((ft_strlen_pez(s, &f) + 1), sizeof(char));
		while (s[i] == 32 && s[i])
			i++;
		while (s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|')
		{
			if (s[i] && s[i] == SQUT)
			{
				i++;
				while (s[i] && s[i] != SQUT)
					i++;
			}
			if (s[i] && s[i] == DQUT)
			{
				i++;
				while (s[i] && s[i] != DQUT)
					i++;
			}
			i++;
		}
		if (s[i] == '<' || s[i] == '>')
		{
			new[k][j++] = s[i++];
			if ((s[i - 1] == '<' && s[i] == '<') || (s[i - 1] == '>' && s[i] == '>'))
				new[k][j++] = s[i++];
			while (s[i] == 32)
				new[k][j++] = s[i++];
			while (!ft_iscut(s[i]))
			{
				if (s[i] && s[i] == SQUT)
				{
					new[k][j++] = s[i++];
					while (s[i] && s[i] != SQUT)
						new[k][j++] = s[i++];
					if (s[i])
						new[k][j++] = s[i++];
				}
				else if (s[i] && s[i] == DQUT)
				{
					new[k][j++] = s[i++];
					while (s[i] && s[i] != DQUT)
						new[k][j++] = s[i++];
					if (s[i])
						new[k][j++] = s[i++];
				}
				else
					new[k][j++] = s[i++];
			}
		}
		k++;
		if (!s[i] || s[i] == '|')
			break ;
	}
	new[k] = NULL;
	if (s[i] == '|')
		meta->flag = 1;
	return (new);
}
/*
int		main()
 
	char **str;
	t_mish a;
	//str = ft_splitermux(" e ch\"a '  ' \" ciao   'a'", &a);
	//str = ft_splitermux(" e cha ' as ' ci 'ao", &a);
	//str = ft_splitermux("cia'o smasb ' ", &a);
	//str = ft_splitermux("ciao a' a\"", &a);
	//str = ft_splitermux(" a'cane ' ' ssss ", &a); // CONTROLLARE
	//str = ft_splitermux(" \"ciao ", &a);
	//str = ft_splitermux(" \'ciao ", &a);
	//str = ft_splitermux("ciao\"$USERzzzzz'\"", &a); //con il ./minishell non stampa, qui stampa ok
	//str = ft_splitermux("ciao $USERs'", &a);
	int i = 0;

	while (str[i]) 
		printf("%s\n", str[i++]);
}
*/
