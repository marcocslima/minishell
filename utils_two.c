/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:59:29 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/01 15:07:27 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_if_slicer(char *s)
{
	int		i;
	int		len;
	char	slicers[4];

	ft_strlcpy(slicers, ";|<>", 5);
	len = ft_strlen(s);
	i = -1;
	if (len == 1)
		while (++i < 4)
			if (slicers[i] == s[0])
				return (1);
	return (0);
}
