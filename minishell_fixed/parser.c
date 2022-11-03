/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:36:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/11/04 00:32:03 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_slc_seq(t_data **data)
{
	t_cursors	*crs;

	init_crs(&crs);
	while ((*data)->input[++crs->l])
		if ((*data)->slicers_types[crs->l] != 0)
			crs->i++;
	(*data)->slicers_seq = ft_calloc(crs->i + 1, sizeof(int));
	while ((*data)->input[++crs->m])
	{
		if ((*data)->slicers_types[crs->m] != 0)
		{
			(*data)->slicers_seq[crs->j] = (*data)->slicers_types[crs->m];
			crs->j++;
		}
	}
	(*data)->qtd_cmds = crs->j + 1;
	(*data)->slicers_seq[crs->j] = 0;
	free(crs);
}

void	parser_in_qtes_exec(t_data **data, char input_seq[], t_cursors	*crs,
	char slicers[])
{
	while (++crs->l < 4)
	{
		while (input_seq[crs->k])
		{
			if (input_seq[crs->k] == '"' || input_seq[crs->k] == '\'')
				crs->c = input_seq[crs->k];
			if (input_seq[crs->k] == crs->c)
			{
				if (crs->flag == 0)
					crs->flag = 1;
				else if (crs->flag == 1)
					crs->flag = 0;
			}
			if (crs->flag == 1 && input_seq[crs->k] == slicers[crs->l])
			{
				input_seq[crs->k] = 1;
				(*data)->tokens[crs->w] = 0;
				crs->w++;
			}
			crs->k++;
		}
		crs->k = 0;
	}
}

char	*parser_in_quotes(t_data **data)
{
	char		*input_seq;
	char		slicers[4];
	t_cursors	*crs;

	init_crs(&crs);
	ft_memmove(slicers, ";|<>", 4);
	crs->len = ft_strlen((*data)->input);
	input_seq = ft_calloc(crs->len + 1, sizeof(char));
	while ((*data)->input[crs->j])
	{
		input_seq[crs->j] = (*data)->input[crs->j];
		crs->j++;
	}
	parser_in_qtes_exec(data, input_seq, crs, slicers);
	free(crs);
	return (input_seq);
}

int	parser_middle(t_data **data, t_cursors *cursor, char token[],
	char slicers[])
{
	int		s;
	int		t;

	s = -1;
	while (++s < 4)
	{
		init_crs(&cursor);
		t = 0;
		while (token[t] != slicers[s])
			t++;
		if (get_slicers(data, cursor, slicers[s], t) == 1)
			return (1);
		free(cursor);
	}
	free((*data)->tmp);
	return (0);
}

int	parser(t_data **data)
{
	char		token[9];
	char		slicers[4];
	t_cursors	*cursor;
	int			i;
	int			t;

	i = -1;
	g_data = *data;
	init_crs(&cursor);
	ft_strlcpy(token, ";|'\" $\\<>", 10);
	ft_memmove(slicers, ";|<>", 4);
	g_data->tokens = ft_calloc(9, sizeof(size_t));
	g_data->len_tokens = ft_calloc(9, sizeof(int));
	g_data->tmp = parser_in_quotes(&g_data);
	while (++i < 9)
		get_token(&g_data, token[i], i);
	parser_middle(&g_data, cursor, token, slicers);
	get_slc_seq(&g_data);
	get_cmds(&g_data, cursor);
	t = 0;
	while (++t < i)
		free(g_data->tokens[t]);
	free(g_data->tokens);
	return (0);
}
