/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/24 16:20:34 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*pathexec(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (cmd);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	free(paths);
	return (0);
}

char	*cmd_space_substitution(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'' || argv[i] == '\"')
		{
			i++;
			if (argv[i] == '\'' || argv[i] == '\"')
				i++;
			while (argv[i] != '\'' && argv[i] != '\"' && argv[i])
			{
				if (argv[i] == ' ')
					argv[i] = 1;
				i++;
			}
		}
		i++;
	}
	if (argv[i] != '\0')
		argv[i] = '\0';
	return (argv);
}

char	**cmd_one_substitution(char **cmd)
{
	int		i;
	int		x;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'' || cmd[i][0] == '\"')
		{
			x = 1;
			if (cmd[i][x] == '\'' || cmd[i][x] == '\"')
				x++;
			while ((cmd[i][x] != '\'' && cmd[i][x] != '\"' ) && cmd[i][x])
			{
				if (cmd[i][x] == 1)
				cmd[i][x] = ' ';
				x++;
			}
			if (cmd[i][x + 1] != '\0' )
				x++;
			one_substitution_2(cmd, i, x);
		}
		i++;
	}
	return (cmd);
}

void	one_substitution_2(char **cmd, int i, int x)
{
	char	*tmp;

	tmp = ft_substr(cmd[i], 1, x - 1);
	free(cmd[i]);
	cmd[i] = tmp;
}

void	path_error(char *path, char **cmd)
{
	int		i;

	i = -1;
	if (!path)
	{
		while (cmd[i++])
			free(cmd[i]);
		free(cmd);
	}
}

void	execute(char *argv, t_data **data)
{
	char	**cmd;
	char	*path;

	cmd_space_substitution(argv);
	cmd = ft_split(argv, ' ');
	cmd_one_substitution (cmd);
	if (cmd[0] == NULL)
	{
		free(cmd[0]);
		free(cmd);
	}
	path = pathexec(cmd[0], (*data)->envp);
	clean_data(data);
	if (execve(path, cmd, (*data)->envp) == -1)
		exit(exec_error_msg(argv));
}

void	execute_pipe(char *argv, t_data **data, t_cursors *crs)
{
	char	**cmd;
	char	*path;
	pid_t	pid;
	int		status;

	signal(SIGINT, child_signal_handler);
	pid = fork();
	if (pid == 0)
	{
		cmd_space_substitution(argv);
		cmd = ft_split(argv, ' ');
		cmd_one_substitution (cmd);
		if (cmd[0] == NULL)
		{
			free(cmd[0]);
			free(cmd);
		}
		path = pathexec(cmd[0], (*data)->envp);
		if (execve(path, cmd, (*data)->envp) == -1)
		{
			free(cmd);
			free(path);
			clean_all(data, crs);
			exit(exec_error_msg(argv));
		}
	}
	waitpid(pid, &status, 0);
	if ( WIFEXITED(status) )
        (*data)->exit_return = WEXITSTATUS(status);
//	clean_data(data);
}

void	ft_pipe(t_data **data, int i, int flag, t_cursors *crs)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	signal(SIGINT, child_signal_handler);
	if (ft_memcmp((*data)->cmds[i][0], "echo", 5))
	{
		pipe (pipefd);
		pid = fork();
		if (pid == 0)
		{
			close (pipefd[IN]);
			dup2 (pipefd[OUT], STDOUT);
			if (flag == 8)/* adicionado */
			{// adicionado
				crs->flagpipe = 0;/* adicionado */
				ft_input(data, crs);// adicionado
				crs->flagpipe = 1;// adicionado
			}// adicionado
			else// adicionado
				builtin_execute(data, i, flag, crs);
		}
		waitpid(pid, &status, 0);
		if ( WIFEXITED(status) )
        	(*data)->exit_return = WEXITSTATUS(status);
		close(pipefd[OUT]);
		dup2(pipefd[IN], STDIN);
		if (crs->flagpipe == 1)// adicionado
			exit(0); // adicionado
	}
}
