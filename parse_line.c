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

char	*ft_parse_word(char *line, t_mish *meta)
{
	int		i;
	int		n;
	char	*newline;

	i = 0;
	newline = NULL;
	if (line[0] == '~' && !line[1] )
	{
		newline = ft_env_value("HOME", meta->env, meta, 0);
		ft_free((void **) &line);
		return (newline);
	}
	if (line[0] == '~' && line[1] == '/')
	{
		newline = ft_env_value("HOME", meta->env, meta, 0);
		newline = ft_linejoin(newline, "/", 1);
		i += 2;
	}
	while (line[i])
	{
		n = 0;
		while (line[i + n] && line[i + n] != SQUT &&
				line[i + n] != DQUT && line[i + n] != '$')
			n++;
		newline = ft_linejoin(newline, &line[i], n);
		if (!line[i + n])
			break ;
		i += n;
		char	*value;
		n = 0;
		if (line[i] == '$' && line[i + 1] == '?')
		{
			value = ft_utoa(meta->exit_code); 
			newline = ft_linejoin(newline, value, ft_strlen(value));
			ft_free((void **) &value);
			i += 2;
		}
		else if (line[i] == '$' &&
				(ft_isenv(line[i + 1]) || line[i + 1] == '{'))
		{
			i++;
			if (line[i] == '{')
				i++;
			value = ft_env_value(&line[i], meta->env, meta, 0);
			newline = ft_linejoin(newline, value, ft_strlen(value)); 
			ft_free((void **) &value);
			while (line[i] && ft_isenv(line[i]))
				i++;
			if (line[i] == '}')
				i++;
		}
		else if (line[i] == SQUT)
		{
			i++;
			while (line[i + n] && line[i + n] != SQUT)
				n++;
			newline = ft_linejoin(newline, &line[i], n);
			i += (n + 1);
		}
		else if (line[i] == DQUT)
		{
			i++;
			while (line[i + n] && line[i + n] != DQUT)
			{
				if (line[i + n] == '$' && line[i + n + 1] == '?')
				{
					newline = ft_linejoin(newline, &line[i], n);
					i += n + 2;
					n = 0;
					value = ft_utoa(meta->exit_code); 
					newline = ft_linejoin(newline, value, ft_strlen(value));
					ft_free((void **) &value);
				}
				else if (line[i + n] == '$' &&
						(ft_isenv(line[i + n + 1]) || line[i + n + 1] == '{'))
				{
					newline = ft_linejoin(newline, &line[i], n);
					i += n;
					n = 0;
					i++;
					if (line[i] == '{')
						i++;
					value = ft_env_value(&line[i], meta->env, meta, 0);
					newline = ft_linejoin(newline, value, ft_strlen(value));
					ft_free((void **) &value);
					while (line[i] && ft_isenv(line[i]))
						i++;
				}
				else
					n++;
			}
			newline = ft_linejoin(newline, &line[i], n);
			i += (n + 1);
		}
		else
			newline = ft_linejoin(newline, &line[i++], 1);
	}
	ft_free((void **) &line);
	return (newline);
}
