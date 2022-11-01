/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/01 15:20:09 by mcesar-d         ###   ########.fr       */
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
				crs->input = open((*data)->cmds[i + 1][0], O_RDONLY, S_IRWXU);
		no_input(data, crs, 0);
		i++;
		echo_input_change(data, k, i, j);
		i++;
	}
	crs->flag = 5;
	crs->i2 += 3;
}
