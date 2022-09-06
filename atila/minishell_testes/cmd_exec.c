/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/05 23:00:51 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

int	cmd_check(t_data **data)
{
	int	i;
	int	j;
	int	k;
	char	*cmd2;

	k = 0;
	while ((*data)->cmds[k])
		k++;
	i = 0;
	while ((*data)->cmds[i] && i < k - 1)
	{
		j = 0;
		while ((*data)->cmds[i][j])
		{
			if (!ft_memcmp((*data)->cmds[i][j], "|", 2))
				ft_pipe(data, i, j);
			if (!ft_memcmp((*data)->cmds[i][j], ";", 2))
			{
				builtin_execute(data, i);
			}
			j++;
		}
		i++;
//		builtin_execute(data, i);
	}
//	if (k > 2 && !(*data)->cmds[i - 1][2])
//		cmd2 = strdup((*data)->cmds[i - 1][0]);
//	else
	cmd2 = strdup((*data)->cmds[i][0]);
	ft_strlcat(cmd2, " ", 4096);
//	if (k > 2 && !(*data)->cmds[i - 1][2] && (*data)->cmds[i - 1][1])
//		ft_strlcat(cmd2, (*data)->cmds[i - 1][1], 4096);
//	else if ((*data)->cmds[i][1])
	if ((*data)->cmds[i][1])
		ft_strlcat(cmd2, (*data)->cmds[i][1], 4096);
//	execute(cmd2, data);
	builtin_execute(data, i);
	return (0);
}

void	builtin_execute(t_data **data, int i)
{
		char	*cmd1;
		int	j;

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
		else
			execute (cmd1, data);
}
