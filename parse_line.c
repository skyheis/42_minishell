/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:55:13 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/13 19:39:50 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_linejoin(char *line, char *piece, int n)
{
	int		i;
	int		j;
	char	*newline;

	newline = ft_calloc(ft_strlen(line) + n + 3, sizeof(char));
	if (!newline)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		newline[j] = line[i];
		i++;
		j++;
	}
	i = 0;
	while (piece && (piece[i] && i < n))
	{
		newline[j] = piece[i];
		i++;
		j++;
	}
	ft_free((void **) &line);
	return (newline);
}

char	*ft_env_value(char	*line_key, char **env, t_mish *meta, int i)
{
	char	*key;
	char	*value;

	value = NULL;
	key = ft_strdup(line_key);
	while (key && ft_isenv(key[i]))
		i++;
	key[i] = '\0';
	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key))
			&& env[i][ft_strlen(key)] == '=')
		{
			value = ft_substr(env[i], ft_strlen(key) + 1, ft_strlen(env[i]));
			ft_free((void **) &key);
			return (value);
		}
	}
	value = ft_strdup(ft_envlst_retvalue(meta->ext_env, key));
	if (!value)
		value = ft_calloc(2, sizeof(char));
	ft_free((void **) &key);
	return (value);
}

void	ft_parse_word_else_dquot(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	while (line[prs->i + prs->n] && line[prs->i + prs->n] != DQUT)
	{
		if (line[prs->i + prs->n] == '$' && line[prs->i + prs->n + 1] == '?')
			ft_parse_word_else_dquot(line, meta, newline, prs);
		else if (line[prs->i + prs->n] == '$'
			&& (ft_isenv(line[prs->i + prs->n + 1])
				|| line[prs->i + prs->n + 1] == '{'))
		{
			*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
			prs->i += prs->n + 1;
			prs->n = 0;
			if (line[prs->i] == '{')
				prs->i++;
			prs->value = ft_env_value(&line[prs->i], meta->env, meta, 0);
			*newline = ft_linejoin(*newline, prs->value, ft_strlen(prs->value));
			ft_free((void **) &(prs->value));
			while (line[prs->i] && ft_isenv(line[prs->i]))
				prs->i++;
		}
		else
			prs->n++;
	}
}

static void	ft_parse_word_2(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	while (line[prs->i])
	{
		prs->n = 0;
		while (line[prs->i + prs->n] && line[prs->i + prs->n] != SQUT
			&& line[prs->i + prs->n] != DQUT && line[prs->i + prs->n] != '$')
			prs->n++;
		*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
		if (!line[prs->i + prs->n])
			break ;
		prs->i += prs->n;
		prs->n = 0;
		if (line[prs->i] == '$' && line[prs->i + 1] == '?')
			ft_parse_word_else_1(newline, prs, meta);
		else if (line[prs->i] == '$'
			&& (ft_isenv(line[prs->i + 1]) || line[prs->i + 1] == '{'))
			ft_parse_word_else_2(line, meta, newline, prs);
		else if (line[prs->i] == SQUT)
			ft_parse_word_else_3(line, newline, prs);
		else if (line[prs->i] == DQUT)
			ft_parse_word_2_1(line, meta, newline, prs);
		else
			*newline = ft_linejoin(*newline, &line[prs->i++], 1);
	}
}

char	*ft_parse_word(char *line, t_mish *meta)
{
	t_prs	prs;
	char	*newline;

	prs.i = 0;
	newline = NULL;
	if (line[0] == '~' && !line[1])
	{
		newline = ft_env_value("HOME", meta->env, meta, 0);
		ft_free((void **) &line);
		return (newline);
	}
	if (line[0] == '~' && line[1] == '/')
	{
		newline = ft_env_value("HOME", meta->env, meta, 0);
		newline = ft_linejoin(newline, "/", 1);
		prs.i += 2;
	}
	ft_parse_word_2(line, meta, &newline, &prs);
	ft_free((void **) &line);
	return (newline);
}
