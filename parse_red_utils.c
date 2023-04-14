#include "minishell.h"

void	ft_parse_red_else_1(char *line, int *n,
	char *newline, t_prs *prs)
{
	while (line[prs->i + *n] && line[prs->i + *n] != SQUT
		&& line[prs->i + *n] != DQUT && line[prs->i + *n] != '$')
		*n += 1;
	newline = ft_linejoin(newline, &line[prs->i], *n);
	prs->i += *n;
	*n = 0;
}

void	ft_parse_red_else_2(char *line, t_mish *meta,
	char *newline, t_prs *prs)
{
	(prs->i)++;
	prs->value = ft_env_value(&line[prs->i], meta->env, meta, 0);
	newline = ft_linejoin(newline, prs->value, ft_strlen(prs->value));
	while (line[prs->i] && ft_isenv(line[prs->i]))
		(prs->i)++;
}

void	ft_parse_red_else_3(char *line, int *n,
	char *newline, t_prs *prs)
{
	(prs->i)++;
	while (line[prs->i + *n] && line[prs->i + *n] != SQUT)
		*n += 1;
	newline = ft_linejoin(newline, &line[prs->i], *n);
	prs->i += (*n + 1);
}
