/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitermux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 17:38:16 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* split che ritorna una matrice del comando, escludendo i redirect */

static void	ft_splitermux_bwhile_2(char *s, t_spl *x)
{
	while (s[x->i] && s[x->i] != 32 && s[x->i] != '|')
	{
		while (!ft_iscut(s[x->i]) && s[x->i] != SQUT && s[x->i] != DQUT)
			x->new[x->k][x->j++] = s[x->i++];
		if (s[x->i] && s[x->i] == SQUT)
		{
			x->new[x->k][x->j++] = s[x->i++];
			while (s[x->i] && s[x->i] != SQUT)
				x->new[x->k][x->j++] = s[x->i++];
			if (s[x->i])
				x->new[x->k][x->j++] = s[x->i++];
		}
		if (s[x->i] && s[x->i] == DQUT)
		{
			x->new[x->k][x->j++] = s[x->i++];
			while (s[x->i] && s[x->i] != DQUT)
				x->new[x->k][x->j++] = s[x->i++];
			if (s[x->i])
				x->new[x->k][x->j++] = s[x->i++];
		}
		if (ft_iscut(s[x->i]))
			break ;
	}
}

static void	ft_splitermux_bwhile_1(char *s, t_spl *x)
{
	while (s[x->i] == 32)
		x->i++;
	while (!ft_iscut(s[x->i]))
	{
		if (s[x->i] && s[x->i] == SQUT)
		{
			x->i++;
			while (s[x->i] && s[x->i] != SQUT)
				x->i++;
		}
		else if (s[x->i] && s[x->i] == DQUT)
		{
			x->i++;
			while (s[x->i] && s[x->i] != DQUT)
				x->i++;
		}
		x->i++;
	}
	while (s[x->i] == 32)
		x->i++;
}

static void	ft_splitermux_bwhile_0(char *s, t_spl *x)
{
	x->j = 0;
	x->new[x->k] = ft_calloc ((ft_strmux_pez(s, &(x->f)) + 1), sizeof(char));
	while (s[x->i] == 32 && s[x->i])
		x->i++;
	while ((s[x->i] && s[x->i] == '>') || (s[x->i] && s[x->i] == '<'))
	{
		if (s[x->i] == '>' && s[x->i + 1] == '>')
			x->i += 2;
		else if (s[x->i] == '<' && s[x->i + 1] == '<')
			x->i += 2;
		else
			x->i++;
		ft_splitermux_bwhile_1(s, x);
	}
}

char	**ft_splitermux(char *s, t_mish *meta)
{
	t_spl	x;

	x.k = 0;
	x.i = 0;
	while (s[x.i] == 32)
		x.i++;
	x.f = x.i;
	x.new = (char **) ft_calloc (ft_count_word_mux(s) + 3, sizeof(char *));
	while (s[x.i] && s[x.i] != '|')
	{
		ft_splitermux_bwhile_0(s, &x);
		ft_splitermux_bwhile_2(s, &x);
		x.k++;
		if (!s[x.i] || s[x.i] == '|')
			break ;
	}
	x.new[x.k] = NULL;
	if (s[x.i] == '|')
		meta->flag = 1;
	return (x.new);
}
