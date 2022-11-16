/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/03 21:45:08 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_input(char **p)
{
	char		slicers[4];
	int			ret;
	t_cursors	*crs;

	ft_strlcpy(slicers, ";|<>", 4);
	init_crs(&crs);
	while (p[++crs->l])
		continue ;
	while (++crs->m < 4)
	{
		if (*p[crs->l - 1] == slicers[crs->m])
		{
			crs->l--;
			break ;
		}
	}
	ret = crs->l;
	free(crs);
	return (ret);
}

void	echo_preper(t_data **data, char **input, t_cursors	*crs)
{
	(*data)->exit_return = 0;
	crs->len = len_input(input);
	if (!input[0] || input[0][0] == '\0')
	{
		write(1, "\n", 1);
		(*data)->exit_return = 1;
	}
	crs->i = 0;
	crs->j = 0;
	if ((*data)->qtd_cmds > 1)
		(*data)->qtd_cmds--;
}

void	rotate_char(t_data **data, char *param, char c)
{
	t_cursors	*crs;
	char		*new;

	init_crs(&crs);
	crs->len = ft_strlen(param) + 1;
	new = ft_calloc(crs->len, sizeof(char));
	(*data)->tmp2 = new;
	while (crs->counter <= crs->len - 1)
	{
		if (param[crs->counter] == '\\' && param[crs->counter + 1] == c)
		{
			new[crs->i] = param[crs->counter + 1];
			crs->i++;
			crs->counter++;
			crs->len = crs->len - 1;
		}
		else if (param[crs->counter] != c)
		{
			new[crs->i] = param[crs->counter];
			crs->i++;
		}
		crs->counter++;
	}
	free(crs);
}

void	handle_quotes_middle(char *param, t_cursors *c)
{
	while (param[++c->l])
	{
		if (param[c->l] == '"')
		{
			if (c->l > 0 && param[c->l - 1] != '\\')
				c->i++;
			else if (c->l == 0)
				c->i++;
		}
		else if (param[c->l] == '\'')
		{
			if (c->l > 0 && param[c->l - 1] != '\\')
				c->j++;
			else if (c->l == 0)
				c->j++;
		}
	}
}

int	handle_quotes(t_data **data, char *param, t_cursors *crs)
{
	t_cursors	*c;

	init_crs(&c);
	if (param[0] == '"' || param[0] == '\'')
		handle_quotes_middle(param, c);
	c->len = c->i + c->j;
	if (c->len % 2 != 0)
	{
		free(c);
		return (1);
	}
	if (param[0] == '"' || param[0] == '\'')
		c->q = param[0];
	rotate_char(data, param, c->q);
	free(c);
	crs->w = ft_strlen((*data)->tmp2) + 1;
	crs->m = -1;
	return (0);
}
