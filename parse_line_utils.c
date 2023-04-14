#include "minishell.h"

void	ft_parse_word_else_1(char **newline, t_prs *prs, t_mish *meta)
{
	prs->value = ft_utoa(meta->exit_code);
	*newline = ft_linejoin(*newline, prs->value, ft_strlen(prs->value));
	ft_free((void **) &(prs->value));
	prs->i += 2;
}

void	ft_parse_word_else_2(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	prs->i++;
	if (line[prs->i] == '{')
		prs->i++;
	prs->value = ft_env_value(&line[prs->i], meta->env, meta, 0);
	*newline = ft_linejoin(*newline, prs->value, ft_strlen(prs->value));
	ft_free((void **) &(prs->value));
	while (line[prs->i] && ft_isenv(line[prs->i]))
		prs->i++;
	if (line[prs->i] == '}')
		prs->i++;
}

void	ft_parse_word_else_3(char *line, char **newline, t_prs *prs)
{
	(prs->i)++;
	while (line[prs->i + prs->n] && line[prs->i + prs->n] != SQUT)
		prs->n += 1;
	*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
	prs->i += (prs->n + 1);
}

void	ft_parse_word_else_dquot2(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
	prs->i += prs->n + 2;
	prs->n = 0;
	prs->value = ft_utoa(meta->exit_code);
	*newline = ft_linejoin(*newline, prs->value, ft_strlen(prs->value));
	ft_free((void **) &(prs->value));
}

void	ft_parse_word_2_1(char *line, t_mish *meta,
	char **newline, t_prs *prs)
{
	prs->i++;
	ft_parse_word_else_dquot(line, meta, newline, prs);
	*newline = ft_linejoin(*newline, &line[prs->i], prs->n);
	prs->i += (prs->n + 1);
}
