/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinput_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/13 03:04:17 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_output(t_data **data, t_cursors *crs)
{
	if (((*data)->cmds[crs->i2 + 2] && (*data)->cmds[crs->i2 + 2][0]
		&& !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2)) || ((*data)
			->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][1], ">", 2)))
	{
		if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2)
			&& !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
			crs->output = open((*data)->cmds[crs->i2 + 2][1], O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		else if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2)
			&& ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 2][0], O_CREAT | O_WRONLY
					| O_TRUNC, 0644);
		if (crs->output == -1)
		{
			ft_putstrs("minishell:", (*data)->cmds[crs->i2 + 2][1],
				": Permission denied", STDERR);
			clean_all(data, crs);
			exit (1);
		}
		redir_stdin_out(data, crs);
		return (0);
	}
	return (1);
}

void	redir_stdin(t_data **data, t_cursors *crs)
{
	if (crs->input > 0)
	{
		crs->saved_stdin = dup(STDIN);
		dup2(crs->input, STDIN);
		builtin_execute(data, crs);
		dup2(crs->saved_stdin, STDIN);
		close(crs->saved_stdin);
		close(crs->input);
	}
}

void	redir_stdin_out(t_data **data, t_cursors *crs)
{
	crs->saved_stdin = dup(STDIN);
	dup2(crs->input, STDIN);
	crs->saved_stdout = dup(STDOUT);
	dup2(crs->output, STDOUT);
	no_input(data, crs, 0);
	builtin_execute(data, crs);
	dup2(crs->saved_stdout, STDOUT);
	dup2(crs->saved_stdin, STDIN);
	close(crs->saved_stdin);
	close(crs->input);
	close(crs->output);
	close(crs->saved_stdout);
}

void	no_input(t_data **data, t_cursors *crs, int flag)
{
	if (crs->input == -1)
	{
		if (!ft_memcmp((*data)->cmds[0][0], "<", 1))
			ft_putstrs("minishell: ", (*data)->cmds[crs->i2][1], ": ", STDERR);
		else
			ft_putstrs("minishell: ", (*data)->cmds[crs->i2 + 1][0], ": ",
				STDERR);
		ft_putstrs(strerror(errno), " \n", NULL, STDERR);
		(*data)->exit_return = 1;
		if (flag == 0)
		{
			clean_all(data, crs);
			exit(ERROR);
		}
	}
}
