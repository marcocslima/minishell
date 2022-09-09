/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/08 23:17:33 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

int	len_cmds(t_data **data, t_cursors *crs, int c)
{
	crs->i = 0;
	while ((*data)->cmds[c][crs->i])
		crs->i++;
	return (crs->i);
}

int	cmd_check(t_data **data)
{
	char		*cmd2;
	t_cursors	*crs;

	init_crs(&crs);
	while ((*data)->cmds[crs->k])
		crs->k++;
	while ((*data)->cmds[crs->i] && crs->i < crs->k - 1)
	{
		crs->j = 0;
		crs->flag = 0;
		while ((*data)->cmds[crs->i][crs->j])
		{
			if (!ft_memcmp((*data)->cmds[crs->i][crs->j], "|", 2))
				ft_pipe(data, crs->i, crs->flag);
			if (!ft_memcmp((*data)->cmds[crs->i][crs->j], ">", 2))
				ft_output(data, crs);
			if (!ft_memcmp((*data)->cmds[crs->i][crs->j], "<", 2))
				ft_input(data, crs);
			if (!ft_memcmp((*data)->cmds[crs->i][crs->j], ";", 2))
			{
				crs->flag = 1;
				builtin_execute(data, crs->i, crs->flag);
			}
			crs->j++;
		}
		crs->i++;
	}
	cmd2 = strdup((*data)->cmds[crs->i][0]);
	ft_strlcat(cmd2, " ", 4096);
	if ((*data)->cmds[crs->i][1])
		ft_strlcat(cmd2, (*data)->cmds[crs->i][1], 4096);
	builtin_execute(data, crs->i, crs->flag);
	return (0);
}

void	builtin_execute(t_data **data, int i, int flag)
{
	char	*cmd1;
	int		j;

	j = 2;
	cmd1 = strdup((*data)->cmds[i][j - 2]);
	ft_strlcat(cmd1, " ", 4096);
	if ((*data)->cmds[i][j - 1])
		ft_strlcat(cmd1, (*data)->cmds[i][j - 1], 4096);
	if (!ft_memcmp((*data)->cmds[i][0], "echo", 5))
		ft_echo(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "pwd", 4))
		ft_pwd();
	else if (!ft_memcmp((*data)->cmds[i][0], "cd", 3))
		ft_cd(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "export", 7))
		ft_export(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "unset", 6))
		ft_unset(data, (*data)->cmds[i][1]);
	else if (flag == 0)
		execute (cmd1, data);
	else
		execute_pipe (cmd1, data);
}
