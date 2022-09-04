/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/04 01:01:00 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

//checando qual comando de input
int	cmd_check(t_data **data)
{
	int	i;
	int	j;

	i = -1;
	while ((*data)->cmds[i++])
	{
		j = 0;
		while ((*data)->cmds[i][j])
		{
			if (!ft_memcmp((*data)->cmds[i][j], "|", 2))
				ft_pipe(data, i, j);
			j++;
		}
		builtin_execute(data, i);
	}
	return (0);
}

void	builtin_execute(t_data **data, int i)
{
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
//	}
}
