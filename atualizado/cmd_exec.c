/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/13 02:58:46 by acosta-a         ###   ########.fr       */
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
	if ((*data)->cmds[0] && (*data)->cmds[0][0] && !ft_memcmp((*data)->cmds
		[0][0], "<", 1))
	{
		crs->input = open((*data)->cmds[0][1], O_RDONLY, 0644);
		no_input(data, crs, 1);
		crs->i2++;
	}
	cmd_check_2(data, crs);
	if (crs->i2 < crs->k2 && ft_memcmp((*data)->cmds[crs->i2][0], ">", 2))
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

void	cmd_check_2_1_middle(t_data **data, t_cursors *crs)
{
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
		if ((crs->i2 + (*data)->jump) <= (*data)->qtd_cmds && (*data)->cmds
			[crs->i2 + (*data)->jump] && (crs->i2 == 0 || !ft_memcmp((*data)
					->cmds[crs->i2 + (*data)->jump][0], "echo", 5)))
				crs->i2 = (*data)->jump + crs->i2;
		else
			crs->i2 = (*data)->jump + crs->i2 + 1;
		crs->j2 = 0;
	}
	cmd_check_2_1_middle(data, crs);
	crs->j2++;
}
