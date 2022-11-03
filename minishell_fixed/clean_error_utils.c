/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:24:16 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/01 00:56:53 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char *string, char *string2, char **array)
{
	if (string)
		free(string);
	if (string2)
		free(string2);
	if (array)
		free(array);
}

int	count_cmds(t_data **data)
{
	int	len;
	int	j;
	int	counter;

	j = 0;
	counter = 0;
	len = 0;
	if ((*data)->input)
		len = ft_strlen((*data)->input);
	while (j < len)
	{
		if ((*data)->slicers[j] != 0)
			counter++;
		j++;
	}
	return (counter);
}

int	error_msg(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(ERROR);
}
