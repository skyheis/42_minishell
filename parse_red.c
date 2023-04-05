/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:07:43 by ggiannit          #+#    #+#             */
/*   Updated: 2023/04/04 14:41:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_red(char *line, t_mish *meta)
{
	int	i;
	int	n;
	char	*value;
	char	*newline;

	n = 0;
	newline = NULL;
	if (line && line[0] == '<' && line[1] == '<')
	{
		i = 2;
		newline = ft_linejoin(newline, line, 2);
		while (line[i] == 32)
			i++;
		while (line[i])
		{
			while (line[i + n] && line[i + n] != SQUT && line[i + n] != DQUT)
				n++;
			newline = ft_linejoin(newline, &line[i], n);
			i += n;
			if (line[i] == SQUT)
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
					n++;
				newline = ft_linejoin(newline, &line[i], n);
				i += (n + 1);
			}
		}
	}
	else
	{
		if (line[1] == '>')
			i = 2;
		else
			i = 1;
		newline = ft_linejoin(newline, line, i);
		while (line[i] == 32)
			i++;
		while (line[i])
		{
			while (line[i + n] && line[i + n] != SQUT && line[i + n] != DQUT)
				n++;
			newline = ft_linejoin(newline, &line[i], n);
			i += n;
			n = 0;
			if (line[i] == SQUT)
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
					else if (line[i + n] == '$' && ft_isenv(line[i + n + 1]))
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
		}
	}
	ft_free((void **) &line); //occhio per test
	return (newline);
}
