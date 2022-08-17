/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/17 16:52:19 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell2.h"
/*
void	cmd_space_substitution(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->input[i])
	{
		if ((*data)->input[i] == '\'' || (*data)->input[i] == '\"')
		{
			i++;
			if ((*data)->input[i] == '\'' || (*data)->input[i] == '\"')
				i++;
			while ((*data)->input[i] != '\'' && (*data)->input[i] != '\"' && (*data)->input[i])
			{
				if ((*data)->input[i] == ' ')
					(*data)->input[i] = '9';
				i++;
			}
		}
		i++;
	}
	(*data)->input[i] = '\0';
}
*/
void		parser(t_data **data)
{
	unsigned int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
//	cmd_space_substitution(data);
	while (i <= ft_strlen((*data)->input))
	{
		if((*data)->input[i] == ' ' || (*data)->input[i] == '\0')
		{
			(*data)->pars_inpt[k] = ft_substr((*data)->input, j, i - j);
			j = i;
			printf("pars_inpt[%d] input: %s  ",k,(*data)->pars_inpt[k]);
			k++;
		}
		i++;
	}


}


