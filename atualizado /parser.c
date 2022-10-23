/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:36:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/23 02:23:10 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token(t_data **data, char token, int n)
{
	t_cursors	*crs;

	init_crs(&crs);
	crs->len = ft_strlen((*data)->input);
	while ((*data)->input[++crs->l])
		if ((*data)->input[crs->l] == token)
			crs->k++;
	if (crs->k == 0)
		(*data)->tokens[n] = NULL;
	else
	{
		(*data)->len_tokens[n] = crs->k;
		(*data)->tokens[n] = ft_calloc(crs->k + 1, sizeof(int));
		while (crs->i < crs->k + 1)
		{
			(*data)->tokens[n][crs->i] = 0;
			crs->i++;
		}
		crs->l = -1;
		crs->k = -1;
		while (++crs->l < crs->len)
			if ((*data)->input[crs->l] == token)
				(*data)->tokens[n][++crs->k] = crs->l;
	}
	free(crs);
}

void	get_limits(t_cursors **crs, char **st_cmds, int n, int i)
{
	(*crs)->flag = 0;
	while (i < (*crs)->len)
	{
		if ((st_cmds[n][i] == '\'' || st_cmds[n][i] == '"') && (*crs)->flag
			== 0)
		{
			if (st_cmds[n][i] == '\'')
				(*crs)->q = '\'';
			else if (st_cmds[n][i] == '"')
				(*crs)->q = '"';
			(*crs)->flag = 1;
			(*crs)->begin = i;
		}
		if ((*crs)->q && (*crs)->last < (*crs)->begin)
			(*crs)->last = ft_findrchr(st_cmds[n], (*crs)->q);
		i++;
	}
}

void	str_cat_util(t_data **data, t_cursors *crs, char *prm, int n)
{
	char	new[100];
	char	sr[4];
	int		len;

	len = ft_strlen(prm);
	if (crs->c)
	{
		sr[0] = ' ';
		sr[1] = (char)(*data)->slicers_seq[n];
		sr[2] = crs->c;
		sr[3] = '\0';
		ft_strlcpy(new, prm, len + 4);
		ft_strlcat(new, sr, len + 4);
		ft_strlcpy(prm, new, len + 4);
	}
	else
	{
		sr[0] = ' ';
		sr[1] = (char)(*data)->slicers_seq[n];
		sr[2] = '\0';
		ft_strlcpy(new, prm, len + 3);
		ft_strlcat(new, sr, len + 3);
		ft_strlcpy(prm, new, len + 3);
	}
}

void	rotate(t_data **data)
{
	t_cursors	*crs;
	int			*new;
	int			*tmp;

	init_crs(&crs);
	crs->len = ft_strlen((*data)->input);
	new = ft_calloc(crs->len + 1, sizeof(int));
	while (++crs->i < crs->len)
		new[crs->i - 1] = (*data)->slicers_seq[crs->i];
	tmp = (*data)->slicers_seq;
	(*data)->slicers_seq = new;
	free(tmp);
	free(crs);
}

void	str_cat(t_data **data, char *prm, int n)
{
	t_cursors	*crs;

	init_crs(&crs);
	if (prm)
		crs->len = ft_strlen(prm);
	crs->i = (*data)->crs;
	(*data)->crs = (*data)->crs + crs->len + 1;
	while (crs->i < (*data)->crs)
	{
		if (((*data)->slicers_types[crs->i] == '<'
				&& (*data)->slicers_types[crs->i + 1] == '<')
			|| ((*data)->slicers_types[crs->i] == '>'
				&& (*data)->slicers_types[crs->i + 1] == '>'))
		{
			crs->c = (*data)->slicers_types[crs->i];
			rotate(data);
		}
		crs->i++;
	}
	str_cat_util(data, crs, prm, n);
	free(crs);
}

void	get_params(t_data **data, char *st_cmd, int n)
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
	(*data)->params = ft_split(st_cmd, ' ');
	crs->o = 0;
	if ((*data)->params[crs->o] && (*data)->params[crs->o][0])
		while ((*data)->params[crs->o] && ft_isascii((*data)->params[crs->o]
				[0]) == 1)
			crs->o++;
	if ((*data)->params[crs->o] && ft_isascii((*data)->params[crs->o][0]) != 1)
		(*data)->params[crs->o][0] = '\0';
	get_params_exchange(data, crs, n);
	free(crs);
}

void	get_params_exchange(t_data **data, t_cursors *crs, int n)
{
	while ((*data)->params && (*data)->params[crs->r])
	{
		crs->m = 0;
		while ((*data)->params[crs->r][crs->m])
			if ((*data)->params[crs->r][++crs->m] == 1)
				(*data)->params[crs->r][crs->m] = ' ';
		crs->m = 0;
		crs->r++;
	}
	(*data)->cmds[n] = (*data)->params;
}

void	get_cmds(t_data **data, t_cursors *cursor)
{
	cursor->len = ft_strlen((*data)->input);
	while (cursor->i < cursor->len)
	{
		if ((*data)->slicers[cursor->i] != 0)
			(*data)->input[cursor->i + 1] = 1;
		cursor->i++;
	}
	while (cursor->j < cursor->len)
	{
		if ((*data)->slicers[cursor->j] != 0)
			cursor->counter++;
		cursor->j++;
	}
	(*data)->cmds = ft_calloc(sizeof(char *) ,cursor->counter + 2);
	(*data)->st_cmds = ft_split((*data)->input, 1);
	while (cursor->r < cursor->counter + 1)
	{
		if ((*data)->st_cmds[cursor->r])
			get_params(data, (*data)->st_cmds[cursor->r], cursor->r);
		cursor->r++;
	}
	(*data)->cmds[cursor->r] = NULL;
	free(cursor);
}

void	put_slicer(t_data **data, t_cursors *cursor, char slc, int t)
{
	(*data)->slicers[cursor->k] = (*data)->tokens[t][cursor->i];
	(*data)->slicers_types[cursor->k] = slc;
	reset_conters(&cursor);
}

int	get_slicers(t_data **data, t_cursors *cursor, char slc, int t)
{
	while (cursor->i < (*data)->len_tokens[t])
	{
		reset_conters(&cursor);
		while (cursor->k < (*data)->tokens[t][cursor->i])
		{
			if (((*data)->input[cursor->k] == '\'' || (*data)->input[cursor->k]
					== '"') && cursor->flag == 0 && (*data)->input[cursor->k
					- 1] != '\\')
			{
				cursor->c = (*data)->input[cursor->k];
				cursor->flag = 1;
			}
			if ((*data)->input[cursor->k] == cursor->c && (*data)->input
				[cursor->k - 1] != '\\')
				cursor->counter++;
			if (cursor->counter % 2 == 0 && ((*data)->input[cursor->k + 1]
					== slc) && ((*data)->input[cursor->k] != slc))
				put_slicer(data, cursor, slc, t);
			cursor->k++;
		}
		if (cursor->counter % 2 != 0)
			return (1);
		cursor->i++;
	}
	return (0);
}

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

int	parser(t_data	**data)
{
	char		token[9];
	char		slicers[4];
	t_cursors	*cursor;
	int			i;
	int			s;
	int			t;

	i = -1;
	s = -1;
	ft_strlcpy(token, ";|'\" $\\<>", 10);
	ft_memmove(slicers, ";|<>", 4);
	(*data)->tokens = ft_calloc(9, sizeof(size_t));
	(*data)->len_tokens = ft_calloc(9, sizeof(int));
	while (++i < 9)
		get_token(data, token[i], i);
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
	get_slc_seq(data);
	init_crs(&cursor);
	get_cmds(data, cursor);
	t = 0;
	while (++t < i)
		free((*data)->tokens[t]);
	free((*data)->tokens);
	return (0);
}
