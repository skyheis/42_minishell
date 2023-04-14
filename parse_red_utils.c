#include "minishell.h"

void	ft_parse_red_else_1(char *line, char **newline, t_prs *prs)
{
	while (line[prs->i + prs->n] && line[prs->i + prs->n] != SQUT
		&& line[prs->i + prs->n] != DQUT && line[prs->i + prs->n] != '$')
		prs->n += 1;
	*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
	prs->i += prs->n;
	prs->n = 0;
}

void	ft_parse_red_else_2(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	(prs->i)++;
	prs->value = ft_env_value(&line[prs->i], meta->env, meta, 0);
	*newline = ft_linejoin(*newline, prs->value, ft_strlen(prs->value));
	while (line[prs->i] && ft_isenv(line[prs->i]))
		(prs->i)++;
}

void	ft_parse_red_else_3(char *line, char **newline, t_prs *prs)
{
	(prs->i)++;
	while (line[prs->i + prs->n] && line[prs->i + prs->n] != SQUT)
		prs->n += 1;
	*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
	prs->i += (prs->n + 1);
}
