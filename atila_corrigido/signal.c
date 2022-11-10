/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/09 20:18:17 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int input)
{
//	char	cwd[4097];

	if (input == SIGINT)
	{
		ft_putstr_fd("\n", 1);
//		getcwd(cwd, 4096);
//		ft_putstr_fd("\n", 1);
//		ft_putstr_fd(cwd, 1);
//		ft_putstr_fd(": ", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_signal_handler(int input)
{
	if (input == SIGINT)
		write(2, "\n", 1);
}
