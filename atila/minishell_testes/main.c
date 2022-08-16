/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/16 00:08:19 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//		printf("%s %d\n", copy[i], i);
	}
	return (copy);
}


void	init_struct(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->envp = copy_env(envp, 0);
	(*data)->argv = argv;
	(*data)->input = (char *)ft_calloc(sizeof(char *), 4097);


}

char	*get_home(char **envp)//deletei essa função já que ficou curta e inseri direto no open_prompt, se achar melhor deixar separado tu que sabe, pra mim tanto faz ,deleta ela já caso concorde se não volta pro antigo
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

//	home = get_home(envp);
//função get home embutida abaixo, se concordar pode deletar os comentarios
	while (ft_memcmp("HOME=", *envp, 5))//inicio
		envp++;
	home = *envp + 5;//fim
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin_2("~", cwd + ft_strlen(home));
	ft_putstr_fd( path , 1);
	free(path);
}

void		get_input(t_data **data)//adicionei essa função que está lendo o que for escrito no promp
{
	char	buf;
	char*	bufstring;
	int		ret;
	int		i;

	i = 0;
	bufstring = ft_calloc(sizeof(char *), 2);
	while((ret = read(0 , &buf, 1)) && buf != '\n')
	{
		bufstring[0] = buf;
		bufstring[1] = '\0';
		(*data)->input = ft_strjoin((*data)->input,bufstring);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
//	char	*input;

	if (argc != 1)
		error_msg("Please type only one argument");
	init_struct(&data, argv, envp);
//	signal(SIGQUIT, sig_handler);
	while (1)
	{
		open_prompt(data->envp);
		signal(SIGINT, signal_handler);
		get_input(&data);


	}

	return (0);
}
