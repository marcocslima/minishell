/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:36:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/14 00:26:09 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token(t_data **data, char token, int n)
{
	int	*tok;
	int	lenstr;
	int	i;
	int	t;

	i = -1;
	t = 0;
	lenstr = ft_strlen((*data)->input);
	while ((*data)->input[++i])
		if ((*data)->input[i] == token)
			t++;
	if (t == 0)
		(*data)->tokens[n] = NULL;
	else
	{
		(*data)->len_tokens[n] = t;
		tok = ft_calloc(t, sizeof(int));
		i = -1;
		t = -1;
		while (++i < lenstr)
			if ((*data)->input[i] == token)
				tok[++t] = i;
		(*data)->tokens[n] = tok;
	}
}

void	get_limits(t_cursors **crs, char **st_cmds, int n, int i)
{
	(*crs)->flag = 0;
	while (i < (*crs)->len)
	{
		if (st_cmds[n][i] == '\'' && (*crs)->flag == 0)
		{
			(*crs)->q = '\'';
			(*crs)->flag = 1;
			(*crs)->begin = i;
		}
		else if (st_cmds[n][i] == '"' && (*crs)->flag == 0)
		{
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
	char	*new;
	char	*tmp;
	char	sr[4];

	new = malloc(sizeof(char) * (crs->len + 3));
	tmp = new;
	new = prm;
	free(tmp);
	if (crs->c)
	{
		sr[0] = ' ';
		sr[1] = (char)(*data)->slicers_seq[n];
		sr[2] = crs->c;
		ft_strlcat(new, sr, crs->len + 4);
	}
	else
	{
		sr[0] = ' ';
		sr[1] = (char)(*data)->slicers_seq[n];
		if (new)
			ft_strlcat(new, sr, crs->len + 3);
	}
	prm = new;
}

void	rotate(t_data **data)
{
	t_cursors	*crs;
	int			*new;
	int			*tmp;

	init_crs(&crs);
	crs->len = ft_strlen((*data)->input);
	new = ft_calloc(crs->len, sizeof(int));
	while (++crs->i < crs->len)
		new[crs->i - 1] = (*data)->slicers_seq[crs->i];
	tmp = (*data)->slicers_seq;
	(*data)->slicers_seq = new;
	free(tmp);
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
	//ADICIONAR AO CÓDIGO DO MARCO
	crs->o = 0;
	while ((*data)->params[crs->o] && ft_isascii((*data)->params[crs->o][0]) == 1)
		crs->o++;
	if ((*data)->params[crs->o] && ft_isascii((*data)->params[crs->o][0]) != 1)
		(*data)->params[crs->o][0] = '\0';
	// PRECISA POR NULO APÓS CAPTAR COMANDOS PRA FAZER LEITURA
	while ((*data)->params[crs->r] != NULL)
	{
		while ((*data)->params[crs->r][crs->m])
			if ((*data)->params[crs->r][++crs->m] == 1)
				(*data)->params[crs->r][crs->m] = ' ';
		crs->m = 0;
		crs->r++;
	}
	(*data)->cmds[n] = (*data)->params;
	free(crs);
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
	(*data)->st_cmds = malloc(sizeof(size_t) * cursor->counter + 1);
	(*data)->cmds = malloc(sizeof(size_t) * cursor->counter + 1);
	while (cursor->k < cursor->counter + 1)
		(*data)->cmds[cursor->k++] = malloc(sizeof(size_t));
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

void	get_slicers(t_data **data, t_cursors *cursor, char slc, int t)
{
	while (cursor->i < (*data)->len_tokens[t])
	{
		reset_conters(&cursor);
		while (cursor->k < (*data)->tokens[t][cursor->i])
		{
			if (((*data)->input[cursor->k] == '\'' || (*data)->input[cursor->k] == '"'))
				cursor->q = (*data)->input[cursor->k];
			if (((*data)->input[cursor->k] == '\'' || (*data)->input[cursor->k] == '"') && cursor->flag == 0)
			{
				cursor->c = (*data)->input[cursor->k];
				cursor->flag = 1;
			}
			if ((*data)->input[cursor->k] == cursor->c)
				cursor->counter++;
			if (cursor->counter % 2 == 0 && ((*data)->input[cursor->k + 1] == slc)
				&& ((*data)->input[cursor->k] != slc))
			{
				(*data)->slicers[cursor->k] = (*data)->tokens[t][cursor->i];
				(*data)->slicers_types[cursor->k] = slc;
				reset_conters(&cursor);
			}
			cursor->k++;
		}
	cursor->i++;
	}
}

void	get_slc_seq(t_data **data)
{
	t_cursors	*crs;

	init_crs(&crs);
	while ((*data)->input[++crs->l])
		if ((*data)->slicers_types[crs->l] != 0)
			crs->i++;
	(*data)->slicers_seq = ft_calloc(crs->i, sizeof(int));
	while ((*data)->input[++crs->m])
		if ((*data)->slicers_types[crs->m] != 0)
		{
			(*data)->slicers_seq[crs->j] = (*data)->slicers_types[crs->m];
			crs->j++;
		}
	free(crs);
}

void parser(t_data	**data)
{
	char		token[9] = ";|'\" $\\<>";
	char		slicers[4] = ";|<>";
	t_cursors	*cursor;
	int			i;
	int			s;
	int			t;

	i = -1;
	s = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 9);
	(*data)->len_tokens = ft_calloc(9,sizeof(int));
	while(++i < 9)
		get_token(data, token[i], i);
	while(++s < 4)
	{
		init_crs(&cursor);
		t = 0;
		while(token[t] != slicers[s])
			t++;
		get_slicers(data, cursor, slicers[s], t);
	}
	get_slc_seq(data);
	init_crs(&cursor);
	get_cmds(data, cursor);
}