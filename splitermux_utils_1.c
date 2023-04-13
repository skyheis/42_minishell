/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitermux_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 17:38:44 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strmux_pez_2(char *s, int *f, int *i)
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
}

static void	ft_strmux_pez_1(char *s, int *f)
{
	if (s[*f] == '<' && s[*f + 1] == '<')
		*f += 2;
	else if (s[*f] == '>' && s[*f + 1] == '>')
		*f += 2;
	else
		*f += 1;
	while (s[*f] == 32)
		*f += 1;
	while (!ft_iscut(s[*f]))
	{
		if (s[*f] && s[*f] == SQUT)
		{
			*f += 1;
			while (s[*f] && s[*f] != SQUT)
				*f += 1;
		}
		else if (s[*f] && s[*f] == DQUT)
		{
			*f += 1;
			while (s[*f] && s[*f] != DQUT)
				*f += 1;
		}
		*f += 1;
	}
}

int	ft_strmux_pez(char *s, int *f)
{
	int	i;

	i = 0;
	while (s[*f] == 32)
		*f += 1;
	while ((s[*f] && s[*f] == '<') || (s[*f] && s[*f] == '>'))
	{
		ft_strmux_pez_1(s, f);
		while (s[*f] == 32)
			*f += 1;
	}
	while (s[*f])
	{
		ft_strmux_pez_2(s, f, &i);
		if (ft_iscut(s[*f]))
			break ;
		i++;
		*f += 1;
	}
	return (i);
}
