/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediroutput_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/01 00:20:10 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char c)
{
	t_cursors	*crs;
	char		slicers[4];

	ft_strlcpy(slicers, ";|", 4);
	init_crs(&crs);
	while (crs->i < 2)
	{
		if (c == slicers[crs->i++])
		{
			free(crs);
			return (1);
		}
	}
	free(crs);
	return (0);
}
