/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitermux_utils_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 17:38:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iscut(char c)
{
	if (!c || c == 32 || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	ft_count_word_skip(char *str, int *i)
{
	while (str[*i] && str[*i] != 32)
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

static void	ft_count_word_iter(char *str, int *i)
{
	while ((str[*i] && str[*i] == '>') || (str[*i] && str[*i] == '<'))
	{
		if (str[*i] == '>' && str[*i + 1] == '>')
			*i += 2;
		else if (str[*i] == '<' && str[*i + 1] == '<')
			*i += 2;
		else
			*i += 1;
		while (str[*i] == 32)
			*i += 1;
		while (!ft_iscut(str[*i]))
			*i += 1;
	}
}

int	ft_count_word_mux(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	if (!str)
		return (1);
	while (str && str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		ft_count_word_iter(str, &i);
		if (!ft_count_word_skip(str, &i))
			return (word);
		word++;
	}
	return (word);
}
