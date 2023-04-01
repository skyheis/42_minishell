/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:55:13 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/01 16:59:48 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* parse_word verra' usata ogni volta che viene creato un nodo, tramite
 * la funzione ft_cmdlst_iterstr
 * */

char	*ft_linejoin(char *line, char *piece, int n)
{
	int		i;
	int		j;
	char	*newline;

	newline = ft_calloc(ft_strlen(line) + n + 1, sizeof(char));
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

char	*ft_env_value(char	*line_key, char **env, t_mish *meta)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	value = NULL;
	key = ft_strdup(line_key);
	while (key && ft_isenv(key[i]))
		i++;
	key[i] = '\0';
	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key))
				&& env[i][ft_strlen(key)] == '=') //in teoria ora ok
		{
			value = ft_substr(env[i], ft_strlen(key) + 1, ft_strlen(env[i]));
			ft_free((void **) &key);
			return(value);
		}
	}
	value = ft_envlst_retvalue(meta->ext_env, key);
	if (!value)
		value = ft_calloc(2, sizeof(char));
	ft_free((void **) &key);
	return (value);
}

char	*ft_parse_word(char *line, t_mish *meta)
{
	//itera, se trova '' fa cose, se trova "" fa cose, se trova $ fa cose
	int		i;
	int		n;
	char	*newline;

	i = 0;
	newline = NULL;
	if (line[0] == '~' && !line[1] )//forse gestibile interno
	{
		newline = ft_env_value("HOME", meta->env, meta);
		newline = ft_linejoin(NULL, newline, ft_strlen(newline));
		return (newline);
	}
	if (line[0] == '~' && line[1] == '/')
	{
		newline = ft_env_value("HOME", meta->env, meta);
		newline = ft_linejoin(NULL, newline, ft_strlen(newline));
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

		//ft_parse_word_cond(int *i, char *line, char **newline)
		//int	n;
		char	*value;
		//
		n = 0;
		if (line[i] == '$' && line[i + 1] == '?')
		{
			value = ft_utoa(meta->exit_code); 
			newline = ft_linejoin(newline, value, ft_strlen(value));
			ft_free((void **) &value);
			i += 2;
		}
		if (line[i] == '$' && ft_isenv(line[i + 1]))
		{
			i++;
			value = ft_env_value(&line[i], meta->env, meta);
			newline = ft_linejoin(newline, value, ft_strlen(value)); 
			while (line[i] && ft_isenv(line[i]))
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
				if (line[i + n] == '$' && ft_isenv(line[i + n + 1]))
				{
					newline = ft_linejoin(newline, &line[i], n);
					i += n;
					n = 0;
					i++;
					value = ft_env_value(&line[i], meta->env, meta);
					newline = ft_linejoin(newline, value, ft_strlen(value));
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
			i++;
		//endfun

	}
	ft_free((void **) &line); //occhio per test
	return (newline);
}

/*
int main(int argc, char **argv, char **envp)
{
	char *lol;

	while (1)
	{
		lol = readline("suca: ");
		add_history(lol);
		printf("%s\n", ft_parse_word(lol, envp));
	}
	//printf("%s\n", ft_parse_line(lol, envp));
	return 0;
}
*/
