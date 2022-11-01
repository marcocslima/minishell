/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 19:49:10 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmds(t_data **data, t_cursors *crs, int c)
{
	crs->i2 = 0;
	while ((*data)->cmds[c][crs->i2])
		crs->i2++;
	return (crs->i2);
}

void	cmd_check(t_data **data)
{
	t_cursors	*crs;

	init_crs(&crs);
	cmd_check_2(data, crs);
	if (crs->i2 < crs->k2 && ft_memcmp((*data)->cmds[crs->i2][0], ">",
		2) && ft_memcmp((*data)->cmds[crs->i2][0], ">", 2))
	{
		crs->flag = 1;
		builtin_execute(data, crs);
	}
	dup2(crs->saved_stdin, STDIN);
	free(crs);
}

void	cmd_check_2(t_data **data, t_cursors *crs)
{
	crs->saved_stdin = dup(STDIN);
	if ((*data)->cmds[crs->k2])
		while ((*data)->cmds[crs->k2])
			crs->k2++;
	while (crs->i2 < crs->k2 - 1 && (*data)->cmds[crs->i2])
	{
		crs->j2 = 0;
		crs->flag = 0;
		if ((*data)->cmds[crs->i2] && (*data)->cmds[crs->i2][0][0] == '>')
			crs->j2++;
		if (crs->i2 >= 1 && (*data)->cmds[crs->i2 - 1][2]
			&& (*data)->cmds[crs->i2 - 1][2][0] == '>')
		{
			crs->i2++;
			crs->j2 = 0;
		}
		while (crs->i2 < crs->k2 && (*data)->cmds[crs->i2][crs->j2])
			cmd_check_2_1(data, crs);
		if (crs->i2 < crs->k2 - 1)
			crs->i2++;
	}
}

void	cmd_check_2_1(t_data **data, t_cursors *crs)
{
	if ((*data)->cmds[crs->i2][crs->j2] && !ft_memcmp((*data)->cmds
		[crs->i2][crs->j2], "|", 2))
		ft_pipe(data, crs->i2, crs->flag, crs);
	if ((*data)->cmds[crs->i2][crs->j2] && !ft_memcmp((*data)->cmds
		[crs->i2][crs->j2], ">", 2))
	{
		ft_output(data, crs);
		crs->i2 = (*data)->jump;
		crs->j2 = 0;
	}
	while (crs->flagpipe == 8 && crs->i2 <= crs->k2 && (*data)->cmds
		[crs->i2] && (*data)->cmds[crs->i2][crs->j2] && !ft_memcmp((*data)->cmds
			[crs->i2][crs->j2], "<", 2))
		ft_input(data, crs);
	if (crs->i2 < (*data)->qtd_cmds && (*data)->cmds[crs->i2]
		&& (*data)->cmds[crs->i2][crs->j2] &&
			!ft_memcmp((*data)->cmds[crs->i2][crs->j2], ";", 2))
	{
		crs->flag = 1;
		builtin_execute(data, crs);
	}
	crs->j2++;
}

void	select_echo(t_data **data, t_cursors *crs, char cmd2[])
{
	if (!ft_memcmp((*data)->cmds[crs->i2][0], "echo", 5))
	{
		if (!(*data)->cmds[crs->i2][1])
			write(1, "\n", 1);
		else if (!ft_memcmp((*data)->cmds[crs->i2][1], "$?", 2))
		{
			ft_putnbr_fd((*data)->exit_return, 1);
			write(1, "\n", 1);
		}
		else
		{
			crs->flagecho = 0;
			ft_echo(data, (*data)->cmds[crs->i2], crs);
		}
	}
	else
		builtin_execute_2(data, cmd2, crs);
}
