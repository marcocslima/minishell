/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/03 07:55:55 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char **envp, char var[], int n)
{
	t_cursors	*crs;
	char		**cp_env;
	char		*tmp;

	init_crs(&crs);
	tmp = ft_calloc(n, sizeof(char));
	while (++crs->l < n)
		tmp[crs->l] = var[crs->l];
	cp_env = copy_env(envp, 3);
	while (cp_env[crs->l])
		crs->l++;
	while (--crs->l > 0 && ft_strncmp(tmp, *cp_env, n))
		cp_env++;
	if (crs->l == 0)
		return (0);
	free(tmp);
	free(crs);
	return (*cp_env + n + 1);
}

void	print_echo(t_data *data, t_cursors *crs, char **input, char tp[])
{
	crs->s = 0;
	while (tp[crs->s])
	{
		if (input[crs->i][0] != '\'' && tp[crs->s] == '$'
			&& tp[crs->s + 1] != ' ')
		{
			while (tp[crs->s + crs->counter] && tp[crs->s
					+ crs->counter] != ' ' && tp[crs->s + crs->counter]
				!='"' && tp[crs->s + crs->counter] != '\'')
		crs->counter++;
		crs->ret = get_value(data->envp, &tp[crs->s + 1], crs->counter - 1);
			if (crs->ret)
			{
				ft_putstr_fd(crs->ret, 1);
				crs->s = crs->s + crs->counter;
			}
		}
		if (crs->s < crs->m)
			ft_putchar_fd(tp[crs->s], 1);
		crs->s++;
		if (tp[crs->s] == '\0' && crs->len - crs->i > 1)
			ft_putchar_fd(' ', 1);
	}
	free(data->tmp2);
}

void	ft_echo_while(t_data *data, char **input, t_cursors *crs, char tp[])
{
	while (++crs->m < crs->w)
	{
		if (!verify_if_slicer(input[crs->i]))
			tp[crs->m] = data->tmp2[crs->m];
		else
			tp[crs->m] = '\0';
	}
}

void	ft_echo(t_data *data, char **input, t_cursors	*crs)
{
	char	tp[4097];

	if (crs->input != 0)
		echo_input(data, crs);
	echo_preper(data, input, crs);
	while (++crs->i < crs->len)
	{
		crs->counter = 0;
		if (input[crs->i][crs->j] == '-' && input [crs->i][crs->j + 1] == 'n')
		{
			crs->flagecho = 1;
			crs->i++;
		}
		crs->err = handle_quotes(data, input[crs->i], crs);
		ft_echo_while(data, input, crs, tp);
		if (crs->err == 0)
			print_echo(data, crs, input, tp);
		else
			print_error(crs->err);
	}
	if (crs->flagecho == 0)
		write (1, "\n", 1);
}
