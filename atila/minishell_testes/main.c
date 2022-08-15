/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/16 00:59:31 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include <stdio.h> //deletar

char	**copy_env(char **envp, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;

	while (envp[len])
		len++;
	if (!(copy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (i++ < len - 1)
	{
		copy[i] = ft_strdup(envp[i]);
		printf("%s %d\n", copy[i], i);
	}
	return (copy);
}


void	init_struct(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->envp = copy_env(envp, 0);
//	data->export = (char **)ft_calloc(sizeof(char *), 1);
	(*data)->argv = argv;
//	data->ret = 0;
//	data->str = 0;
//	data->child = 0;
//	ret_len[0] = 1;
//	print_welcome_msg();
}

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin_2(env, "=");
	len = ft_strlen(env);
	i = 0;

	while (envp[i] && ft_strncmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}

char	*get_home(char **envp)
{
	while (ft_memcmp("HOME=", *envp, 5))
		envp++;
	return (*envp + 5);
}


void	open_prompt(char **envp)
{
	char	*home;
	char	cwd[4097];
	char	*path;

	home = get_home(envp); // Substituí a função get_env por essa!!
	//home = get_env(envp, "HOME");
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin_2("~", cwd + ft_strlen(home));
	ft_putstr_fd( path , 1);
	free(path);
}
static void		get_input(char **input)
{
	char	buf;
	int		ret;
	int		i;
	int		count;

	*input = 
}
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	if (argc != 1)
		error_msg("Please type only one argument");
	init_struct(&data, argv, envp);
//	signal(SIGQUIT, sig_handler);
	while (1)
	{
		open_prompt(data->envp);
		signal(SIGINT, signal_handler);
		get_input(char **input);


	}

	return (0);
}
