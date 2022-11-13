/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:57:01 by acosta-a          #+#    #+#             */
/*   Updated: 2022/11/11 02:20:47 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data **data, char *input, t_cursors *crs)
{
	int	i;
	int	p;

	i = 0;
	p = getpid();
	if (input && input[0] != '\0' && input[0] != '|' && input[0]
		!= '>' && input[0] != ';')
	{
		ft_putstrs("No arguments allowed", "\n", 0, 1);
		(*data)->exit_return = 127;
		return (127);
	}
	while ((*data)->envp[i])
	{
		ft_putstrs((*data)->envp[i], "\n", 0, 1);
		i++;
	}
	if (p > 0 && (*data)->cmds[0][1])
	{
		clean_all(data, crs);
		exit(0);
	}
	return (0);
}

char	**copy_env(char **envp, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;
	while (envp[len])
		len++;
	copy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!copy)
		return (0);
	i = -1;
	while (i++ < len - 1)
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}

char	**copy_env2(t_data **data, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;
	while ((*data)->envp[len])
		len++;
	copy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!copy)
		return (0);
	i = -1;
	while (i++ < len - 1)
	{
		copy[i] = ft_strdup((*data)->envp[i]);
		printf("%s %d\n", copy[i], i);
	}
	return (copy);
}

char	**copy__env_unset(char **envp, int add, char *input, t_cursors *crs)
{
	int		i;
	int		j;
	int		len;
	char	**copy;

	len = 0;
	while (envp[len])
		len++;
	copy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!copy)
		return (0);
	i = -1;
	j = -1;
	while (i++ <= len - 1 && j++ <= len - 1)
	{
		if (envp[i] && ft_memcmp(envp[i], input, crs->len) != 0)
			copy[j] = ft_strdup(envp[i]);
		else if (envp[i + 1])
		{
			copy[j] = ft_strdup(envp[i + 1]);
			i++;
		}
	}
	return (copy);
}
