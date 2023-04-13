/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitered_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 16:57:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strred_pez_2(char *s, int *f, int *i)
{
	if (s[*f] == SQUT)
	{
		*i += 1;
		*f += 1;
		while (s[*f] != SQUT)
		{
			*i += 1;
			*f += 1;
		}
	}
	if (s[*f] == DQUT)
	{
		*i += 1;
		*f += 1;
		while (s[*f] != DQUT)
		{
			*i += 1;
			*f += 1;
		}
	}
	*i += 1;
	*f += 1;
}

static void	ft_strred_pez_1(char *s, int *f, int *i)
{
	if ((s[*f] == '<' && s[*f + 1] == '<')
		&& (s[*f] == '>' && s[*f + 1] == '>'))
	{
		*i += 1;
		*f += 1;
	}
	*i += 1;
	*f += 1;
	while (s[*f] == 32)
		*f += 1;
	while (!ft_iscut(s[*f]))
		ft_strred_pez_2(s, f, i);
}

int	ft_strred_pez(char *s, int *f)
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
		ft_strred_pez_1(s, f, &i);
	return (i);
}

static int	ft_count_word_skip(char *str, int *i)
{
	while (str[*i] && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] && str[*i] == SQUT)
		{
			*i += 1;
			while (str[*i] && str[*i] != SQUT)
				*i += 1;
		}
		if (str[*i] && str[*i] == DQUT)
		{
			*i += 1;
			while (str[*i] && str[*i] != DQUT)
				*i += 1;
		}
		if (str[*i] == '|')
			return (0);
		*i += 1;
	}
	return (1);
}

int	ft_count_word_red(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	if (!str)
		return (1);
	while (str && str[i])
	{
		if (!ft_count_word_skip(str, &i))
			return (word);
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
				i++;
		}
		word++;
	}
	return (word);
}
