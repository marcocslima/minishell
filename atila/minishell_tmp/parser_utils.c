/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:36:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/11/03 07:56:18 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_params(t_data *data, char *st_cmd, int n)
{
	t_cursors	*crs;

	init_crs(&crs);
	str_cat(data, st_cmd, n);
	crs->len = ft_strlen(st_cmd);
	get_limits(&crs, &st_cmd, 0, crs->i);
	while (crs->l++ < crs->len)
	{
		if (crs->l > crs->last)
			get_limits(&crs, &st_cmd, 0, crs->i = crs->l);
		if (crs->l > crs->begin && crs->l < crs->last)
			if (st_cmd[crs->l] == ' ')
				st_cmd[crs->l] = 1;
	}
	data->params = ft_split(st_cmd, ' ');
	crs->o = 0;
	if (data->params[crs->o] && data->params[crs->o][0])
		while (data->params[crs->o] && ft_isascii(data->params[crs->o]
				[0]) == 1)
			crs->o++;
	if (data->params[crs->o] && ft_isascii(data->params[crs->o][0]) != 1)
		data->params[crs->o][0] = '\0';
	get_params_exchange(data, crs, n);
	free(crs);
}

void	get_params_exchange(t_data *data, t_cursors *crs, int n)
{
	while (data->params && data->params[crs->r])
	{
		crs->m = 0;
		while (data->params[crs->r][crs->m])
			if (data->params[crs->r][++crs->m] == 1)
				data->params[crs->r][crs->m] = ' ';
		crs->m = 0;
		crs->r++;
	}
	data->cmds[n] = data->params;
}

void	get_cmds(t_data *data, t_cursors *cursor)
{
	cursor->len = ft_strlen(data->input);
	while (cursor->i < cursor->len)
	{
		if (data->slicers[cursor->i] != 0)
			data->input[cursor->i + 1] = 1;
		cursor->i++;
	}
	while (cursor->j < cursor->len)
	{
		if (data->slicers[cursor->j] != 0)
			cursor->counter++;
		cursor->j++;
	}
	data->cmds = ft_calloc(sizeof(char *), cursor->counter + 2);
	data->st_cmds = ft_split(data->input, 1);
	while (cursor->r < cursor->counter + 1)
	{
		if (data->st_cmds[cursor->r])
			get_params(data, data->st_cmds[cursor->r], cursor->r);
		cursor->r++;
	}
	data->cmds[cursor->r] = NULL;
	free(cursor);
}

void	put_slicer(t_data *data, t_cursors *cursor, char slc, int t)
{
	data->slicers[cursor->k] = data->tokens[t][cursor->i];
	data->slicers_types[cursor->k] = slc;
	reset_conters(&cursor);
}

int	get_slicers(t_data *data, t_cursors *cursor, char slc, int t)
{
	while (cursor->i < data->len_tokens[t])
	{
		reset_conters(&cursor);
		while (cursor->k < data->tokens[t][cursor->i])
		{
			if ((data->tmp[cursor->k] == '\'' || data->tmp[cursor->k]
					== '"') && cursor->flag == 0 && data->tmp[cursor->k - 1]
				!= '\\')
			{
				cursor->c = data->tmp[cursor->k];
				cursor->flag = 1;
			}
			if (data->tmp[cursor->k] == cursor->c && data->tmp
				[cursor->k - 1] != '\\')
				cursor->counter++;
			if (cursor->counter % 2 == 0 && (data->tmp[cursor->k + 1]
					== slc) && (data->tmp[cursor->k] != slc))
				put_slicer(data, cursor, slc, t);
			cursor->k++;
		}
		if (cursor->counter % 2 != 0)
			return (1);
		cursor->i++;
	}
	return (0);
}
