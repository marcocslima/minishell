/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/02 02:45:17 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_input(t_data **data, t_cursors *crs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	while ((*data)->cmds[0][k])
		k++;
	k--;
	while (i < crs->k2 - 1 && (*data)->cmds[i])
	{
		if ((*data)->cmds[i] && (*data)->cmds[i][2]
			&& !ft_memcmp((*data)->cmds[i][2], "<", 2) && (*data)->cmds[i + 1]
			&& (*data)->cmds[i + 1][1] && ft_memcmp((*data)->cmds[i + 1][1]
				, "|", 2) && ft_memcmp((*data)->cmds[i + 1][1], "<", 2))
				crs->input = open((*data)->cmds[i + 1][0], O_RDONLY, 0644);
		no_input(data, crs, 0);
		i++;
		echo_input_change(data, k, i, j);
		i++;
	}
	crs->flag = 5;
	crs->i2 += 3;
}

void	echo_input_change(t_data **data, int k, int i, int j)
{
	while ((*data)->cmds[i][j])
	{
		(*data)->cmds[0][k] = (*data)->cmds[i][j];
		(*data)->cmds[i][j] = NULL;
		free((*data)->cmds[i][j]);
		j++;
		k++;
	}
	(*data)->cmds[0][k] = 0;
}
