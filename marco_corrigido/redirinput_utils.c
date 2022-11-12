/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinput_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/12 15:51:58 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
