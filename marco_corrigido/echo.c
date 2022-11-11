/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/11 21:56:52 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char **envp, const char *var, int n)
{
	t_cursors	*crs;
	char		*tmp;
	char		*tmp2;

	init_crs(&crs);
	crs->l = 0;
	tmp = ft_strdup(var);
	tmp = ft_strjoin(tmp, "=");
	while (envp[crs->l])
		crs->l++;
	crs->l--;
	while (crs->l > 0 && ft_strncmp(tmp, envp[crs->l], n + 1)
	)
		crs->l--;
	if (ft_strncmp(tmp, envp[crs->l], n + 1))
	{
		free(tmp);
		free(crs);
		tmp2 = ft_strdup("");
		return (tmp2);
	}
	tmp2 = ft_substr(envp[crs->l], n + 1, ft_strlen(envp[crs->l]) - n);
	free(tmp);
	free(crs);
	return (tmp2);
}

void	print_echo(t_data **data, t_cursors *crs, char **input, char tp[])
{
	while (tp[crs->s])
	{
		if (input[crs->i][0] != '\'' && tp[crs->s] && tp[crs->s] == '$'
			&& tp[crs->s + 1] != ' ')
		{
			while (tp[crs->s + crs->counter] && tp[crs->s
					+ crs->counter] != ' ' && tp[crs->s + crs->counter]
				!='"' && tp[crs->s + crs->counter] != '\'')
		crs->counter++;
		crs->ret = get_value((*data)->envp, &tp[crs->s + 1], crs->counter - 1);
			if (crs->ret)
			{
				ft_putstr_fd(crs->ret, 1);
				crs->s = crs->s + crs->counter;
				free(crs->ret);
				break ;
			}
		}
		if (crs->s < crs->m)
			ft_putchar_fd(tp[crs->s], 1);
		crs->s++;
		if (tp && tp[crs->s] == '\0' && crs->len - crs->i > 1)
			ft_putchar_fd(' ', 1);
	}
	free((*data)->tmp2);
}

void	ft_echo_while(t_data **data, char **input, t_cursors *crs, char tp[])
{
	while (++crs->m < crs->w)
	{
		if (!verify_if_slicer(input[crs->i]))
			tp[crs->m] = (*data)->tmp2[crs->m];
		else
			tp[crs->m] = '\0';
	}
}

void	ft_echo_w_two(t_data **data, char **input, t_cursors *crs, char tp[])
{
	while (++crs->i < crs->len)
	{
		crs->counter = 0;
		if (input[crs->i][crs->j] == '-' && input [crs->i][crs->j + 1] == 'n')
		{
			crs->flagecho = 1;
			if (input[crs->i][crs->j + 2] == 0 && !input[crs->i + 1])
				break ;
			crs->i++;
		}
		crs->err = handle_quotes(data, input[crs->i], crs);
		ft_echo_while(data, input, crs, tp);
		if (crs->err == 0)
		{
			crs->s = 0;
			print_echo(data, crs, input, tp);
		}
		else
			print_error(crs->err);
	}
}

void	ft_echo(t_data **data, char **input, t_cursors	*crs)
{
	char	tp[4097];

	if (crs->input != 0)
		echo_input(data, crs);
	echo_preper(data, input, crs);
	ft_echo_w_two(data, input, crs, tp);
	if (crs->flagecho == 0)
		write (1, "\n", 1);
}
