/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediroutput_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/13 02:57:00 by acosta-a         ###   ########.fr       */
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

void	no_output(t_data **data, t_cursors *crs, char *jc, char **ncmd)
{
	if (crs->output == -1)
	{
		ft_putstrs("minishell: ", ncmd[crs->k], ": ", STDERR);
		ft_putstrs(strerror(errno), " \n", NULL, STDERR);
		(*data)->exit_return = 1;
		destroy_pointers_char(ncmd);
		free(jc);
		clean_all(data, crs);
		exit(ERROR);
	}
}
