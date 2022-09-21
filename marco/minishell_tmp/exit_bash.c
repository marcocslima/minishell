/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/21 04:19:02 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error_msg(char *path)
{
	int	fd;
	DIR *folder;

	fd = open(path, O_WRONLY);
	if (path)
		folder = opendir(path);
	ft_putstrs("minishell: ", path, NULL ,STDERR);
//	if (ft_strchr(path, '/') == NULL)
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(": command not found", STDERR);
		exit (127);
	}
	else if (fd == -1 && folder == NULL)
	{
		ft_putstr_fd ("No such file or directory", STDERR);
		exit (127);
	}
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd (": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd (": Permission denied", STDERR);
	if (folder)
		closedir(folder);
	close(fd);
	exit (126);
}

void	signal_handler_bash(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(0);
	}
}

void	ft_bash(t_data **data)
{
//	char	*home_path;
	char	cwd[256];
	char	*path;
//	int		i;
//	char	*cmd;
	pid_t	pid;
	int status;
	pid = fork();
//	i = 0;
	path = getcwd(cwd, sizeof(cwd));
	path = ft_strjoin_2(path, "/");
	path = ft_strjoin_2(path, (*data)->cmds[0][0]);
//	home_path = find_env_val(data, "HOME");
//	if (execve(path, (char *[]){0}, (*data)->envp)  == -1)
//		exit(ERROR);
	if (pid == 0)
	{
		signal(SIGINT, signal_handler_bash);
		if (execve(path, (char *[]){0}, (*data)->envp)  == -1)
//			exit(ERROR);
			exec_error_msg(path);
	}
	else
	{
		waitpid(pid, &status, 0);
		return ;
	}


//	ft_cd_home(data, home_path, i, input);
//	if ((*data)->exit_return != 2)
//		return ;

}
int	error_msg(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(ERROR);
}

int	no_error_msg(char *message)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
//	if (stack->array_a[0])
	{
//		free(stack->array_a);
//		free(stack->array_b);
	}
	exit(0);
}

