/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/10 01:03:49 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_execute_if(t_data **data, t_cursors *crs)
{
	if ((*data)->cmds[crs->i2][crs->s]
		&& ft_strncmp((*data)->cmds[crs->i2][crs->s], "<", 1)
		&& ft_strncmp((*data)->cmds[crs->i2][crs->s], ">", 1)
		&& ft_strncmp((*data)->cmds[crs->i2][crs->s], "|", 1)
		&& ft_strncmp((*data)->cmds[crs->i2][crs->s], ";", 1))
	{
		(*data)->tmp2 = ft_strjoin((*data)->tmp2, " ");
		(*data)->tmp2 = ft_strjoin((*data)->tmp2,
				(*data)->cmds[crs->i2][crs->s]);
	}
}

void	builtin_execute(t_data **data, t_cursors *crs)
{
	char	cmd2[4096];

	crs->s = 1;
	if (((*data)->cmds[crs->i2][0] && crs->i > 0 && crs->i2 > 0
		&& (*data)->cmds[crs->i2 - 1][2] && ft_strncmp((*data)->cmds
		[crs->i2 - 1][2], ">", 1)) || ((*data)->cmds[crs->i2][0]
		&& crs->i == 0))
		(*data)->tmp2 = ft_strdup((*data)->cmds[crs->i2][0]);
	while ((*data)->cmds[crs->i2] && (*data)->cmds[crs->i2][crs->s])
	{
		builtin_execute_if(data, crs);
		crs->s++;
	}
	crs->len = ft_strlen((*data)->tmp2);
	ft_bzero(cmd2, 1000);
	ft_memcpy(cmd2, (*data)->tmp2, crs->len);
	free((*data)->tmp2);
	select_echo(data, crs, cmd2);
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

void	builtin_execute_2(t_data **data, char *cmd1, t_cursors *crs)
{
	if (!ft_memcmp((*data)->cmds[crs->i2][0], "./", 2) ||
			!ft_memcmp((*data)->cmds[crs->i2][0], "../", 3))
		ft_bash(data);
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "pwd", 4))
		ft_pwd();
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "cd", 3))
		ft_cd(data, (*data)->cmds[crs->i2][1], crs->i2);
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "export", 7))
		ft_export(data, (*data)->cmds[crs->i2][1], crs);
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "unset", 6))
		ft_unset(data, (*data)->cmds[crs->i2][1]);
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "env", 4))
		ft_env(data, (*data)->cmds[crs->i2][1], crs);
	else if (!ft_memcmp((*data)->cmds[crs->i2][0], "exit", 5))
		ft_exit(data, crs);
	else if (crs->flag == 0)
		execute(cmd1, data);
	else
		execute_pipe(cmd1, data, crs);
}
