/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitered.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:32:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 16:38:57 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* split che ritorna una matrice con i soli redirect */

static void	ft_splitered_bwhile_2(char *s, t_spl *x)
{
	while (s[x->i] == 32)
		x->new[x->k][x->j++] = s[x->i++];
	while (!ft_iscut(s[x->i]))
	{
		if (s[x->i] && s[x->i] == SQUT)
		{
			x->new[x->k][x->j++] = s[x->i++];
			while (s[x->i] && s[x->i] != SQUT)
				x->new[x->k][x->j++] = s[x->i++];
			if (s[x->i])
				x->new[x->k][x->j++] = s[x->i++];
		}
		else if (s[x->i] && s[x->i] == DQUT)
		{
			x->new[x->k][x->j++] = s[x->i++];
			while (s[x->i] && s[x->i] != DQUT)
				x->new[x->k][x->j++] = s[x->i++];
			if (s[x->i])
				x->new[x->k][x->j++] = s[x->i++];
		}
		else
			x->new[x->k][x->j++] = s[x->i++];
	}
}

static void	ft_splitered_bwhile_1(char *s, t_spl *x)
{
	if (s[x->i] == '<' || s[x->i] == '>')
	{
		x->new[x->k][x->j++] = s[x->i++];
		if ((s[x->i - 1] == '<' && s[x->i] == '<')
			|| (s[x->i - 1] == '>' && s[x->i] == '>'))
			x->new[x->k][x->j++] = s[x->i++];
		ft_splitered_bwhile_2(s, x);
	}
}

static void	ft_splitered_bwhile_0(char *s, t_spl *x)
{
	x->j = 0;
	x->new[x->k] = ft_calloc ((ft_strred_pez(s, &(x->f)) + 1), sizeof(char));
	while (s[x->i] == 32 && s[x->i])
		x->i++;
	while (s[x->i] && s[x->i] != '<' && s[x->i] != '>' && s[x->i] != '|')
	{
		if (s[x->i] && s[x->i] == SQUT)
		{
			x->i++;
			while (s[x->i] && s[x->i] != SQUT)
				x->i++;
		}
		if (s[x->i] && s[x->i] == DQUT)
		{
			x->i++;
			while (s[x->i] && s[x->i] != DQUT)
				x->i++;
		}
		x->i++;
	}
}

char	**ft_splitered(char *s, t_mish *meta)
{
	t_spl	x;

	x.k = 0;
	x.i = 0;
	x.f = 0;
	x.new = (char **) ft_calloc (ft_count_word_red(s) + 1, sizeof(char *));
	while (s[x.i] && s[x.i] != '|')
	{
		ft_splitered_bwhile_0(s, &x);
		ft_splitered_bwhile_1(s, &x);
		x.k++;
		if (!s[x.i] || s[x.i] == '|')
			break ;
	}
	x.new[x.k] = NULL;
	if (s[x.i] == '|')
		meta->flag = 1;
	return (x.new);
}
