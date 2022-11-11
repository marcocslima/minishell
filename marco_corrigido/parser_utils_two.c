/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:36:21 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/11/09 16:15:19 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token(t_data **data, char token, int n)
{
	t_cursors	*crs;
	int			*tok;

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
		tok = ft_calloc(crs->k + 1, sizeof(int));
		while (crs->i < crs->k + 1)
			tok[crs->i++] = 0;
		crs->k = -1;
		while (++crs->n < crs->len)
			if ((*data)->input[crs->n] == token)
				tok[++crs->k] = crs->n;
		(*data)->tokens[n] = tok;
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
	char	new[4096];
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
