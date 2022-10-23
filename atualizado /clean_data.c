/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:52:45 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/23 00:52:23 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//DA PRA DELETAR ESSA FUNÇÃO ABAIXO A PRINCIPIO
void	destroy_pointers_int(int **p)
{
	int i = -1;
	if (p[i + 1])
		while (p[++i])
			free(p[i]);
	free(p);
}

void	destroy_pointers_char(char **p)
{
	int	i;

	i = -1;
	if (p[i + 1])
		while (p[++i])
			if (p[i])
				free(p[i]);
	free(p);
}

void	destroy_mat_char(t_data **data, char ***p, t_cursors *crs)
{
	init_crs(&crs);
	crs->len = count_cmds(data);
	while (crs->i < crs->len + 1)
	{
		crs->j = 0;
		while (p[crs->i][crs->j])
		{
			free(p[crs->i][crs->j]);
			crs->j++;
		}
		free(p[crs->i]);
		crs->i++;
	}
	free(p);
	free(crs);
}

void	clean_data(t_data **data)
{
	t_cursors	*crs;

	init_crs(&crs);
	if ((*data)->cmds)
		destroy_mat_char(data, (*data)->cmds, crs);
	free((*data)->len_tokens);
	free((*data)->slicers);
	free((*data)->slicers_types);
	free((*data)->slicers_seq);
	free((*data)->input);
	destroy_pointers_char((*data)->st_cmds);
	(*data)->crs = 0;
	free(crs);
}

void	clean_all(t_data **data, t_cursors *crs)
{
	rl_clear_history();
	clean_data(data);
	destroy_pointers_char((*data)->envp);
	//destroy_pointers_char((*data)->argv); NÃO É MALLOCADO
	(*data)->argv = '\0';
//	free((*data)->tmp);
	free((*data)->dollar);
	free(crs);
	free((*data));
}

void	free_paths(char *home_path, char *pathcd)
{
	free(pathcd);
	free(home_path);
}
