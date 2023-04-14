/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:07:43 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/06 17:52:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_red_if_2(char *line, int *i, char *newline)
{
	*i = 2;
	newline = ft_linejoin(newline, line, 2);
	while (line[*i] == 32)
		*i += 1;
}

static void	ft_parse_red_if(char *line, char *newline, int n, t_prs *prs)
{
	ft_parse_red_if_2(line, &prs->i, newline);
	while (line[prs->i])
	{
		while (line[prs->i + n] && line[prs->i + n] != SQUT
			&& line[prs->i + n] != DQUT)
			n++;
		newline = ft_linejoin(newline, &line[prs->i], n);
		prs->i += n;
		if (line[prs->i] == SQUT)
		{
			prs->i++;
			while (line[prs->i + n] && line[prs->i + n] != SQUT)
				n++;
			newline = ft_linejoin(newline, &line[prs->i], n);
			prs->i += (n + 1);
		}
		else if (line[prs->i] == DQUT)
		{
			prs->i++;
			while (line[prs->i + n] && line[prs->i + n] != DQUT)
				n++;
			newline = ft_linejoin(newline, &line[prs->i], n);
			prs->i += (n + 1);
		}
	}
}

void	ft_parse_red_else_dquot(char *line, t_mish *meta,
	char *newline, t_prs *prs)
{
	while (line[prs->i + prs->n] && line[prs->i + prs->n] != DQUT)
	{
		if (line[prs->i + prs->n] == '$' && line[prs->i + prs->n + 1] == '?')
		{
			newline = ft_linejoin(newline, &line[prs->i], prs->n);
			prs->i += prs->n + 2;
			prs->n = 0;
			prs->value = ft_utoa(meta->exit_code);
			newline = ft_linejoin(newline, prs->value, ft_strlen(prs->value));
			ft_free((void **) &(prs->value));
		}
		else if (line[prs->i + prs->n] == '$'
			&& ft_isenv(line[prs->i + prs->n + 1]))
		{
			newline = ft_linejoin(newline, &line[prs->i], prs->n);
			prs->i += prs->n + 1;
			prs->n = 0;
			prs->value = ft_env_value(&line[prs->i], meta->env, meta, 0);
			newline = ft_linejoin(newline, prs->value, ft_strlen(prs->value));
			while (line[prs->i] && ft_isenv(line[prs->i]))
				prs->i++;
		}
		else
			prs->n++;
	}
}

static void	ft_parse_red_else(char *line, t_mish *meta,
	char *newline, t_prs *prs)
{
	prs->n = 0;
	while (line[prs->i])
	{
		ft_parse_red_else_1(line, &prs->n, newline, prs);
		if (line[prs->i] == '$' && line[prs->i + 1] == '?')
		{
			prs->value = ft_utoa(meta->exit_code);
			newline = ft_linejoin(newline, prs->value, ft_strlen(prs->value));
			ft_free((void **) &(prs->value));
			prs->i += 2;
		}
		else if (line[prs->i] == '$' && ft_isenv(line[prs->i + 1]))
			ft_parse_red_else_2(line, meta, newline, prs);
		else if (line[prs->i] == SQUT)
			ft_parse_red_else_3(line, &prs->n, newline, prs);
		else if (line[prs->i] == DQUT)
		{
			prs->i++;
			ft_parse_red_else_dquot(line, meta, newline, prs);
			newline = ft_linejoin(newline, &line[prs->i], prs->n);
			prs->i += (prs->n + 1);
		}
	}
}

char	*ft_parse_red(char *line, t_mish *meta)
{
	int		n;
	t_prs	prs;
	char	*newline;

	n = 0;
	prs.i = 0;
	newline = NULL;
	if (line && line[0] == '<' && line[1] == '<')
		ft_parse_red_if(line, newline, n, &prs);
	else
	{
		if (line[1] == '>')
			prs.i = 2;
		else
			prs.i = 1;
		newline = ft_linejoin(newline, line, prs.i);
		while (line[prs.i] == 32)
			(prs.i)++;
		ft_parse_red_else(line, meta, newline, &prs);
	}
	ft_free((void **) &line);
	return (newline);
}
