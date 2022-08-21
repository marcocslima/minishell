/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/17 14:55:10 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <stdio.h> //deletar
# define ERROR 1
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define COLON 7
# define ECHO 10
# define CD 11
# define PWD 12
# define EXPORT 13
# define UNSET 14
# define ENV 15
# define EXIT 16

typedef struct s_data
{
	char	**envp;
	char	**argv;
	int		**tokens;
	int		argc;
	char	*input;
	char	**pars_inpt;
	char	**pars_type;
	char	*path;
}	t_data;

int		no_error_msg(char *message);
int		error_msg(char *message);
void	signal_handler(int	input);
char	*ft_strjoin_2(char *s1, char *s2);
void	parser(t_data **data);
#endif
