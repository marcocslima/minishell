/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:57:01 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/05 08:22:26 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data **data, char *input)
{
	int	i;

	i = 0;
	if (input && input[0] != '\0' && input[0] != '|' && input[0]
		!= '>' && input[0] != ';')
	{
		ft_putstrs("No arguments allowed", "\n", 0, 1);
		return (127);
	}
	while ((*data)->envp[i])
	{
		ft_putstrs((*data)->envp[i], "\n", 0, 1);
		i++;
	}
	int p = getpid();
	if(p > 0)
		kill(p, SIGTERM);
	return (0);

}
