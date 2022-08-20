/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:19:15 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/08/14 00:37:39 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	char comando[64];
	int status;
	printf("MY PROMPT ");
	memset(comando, '\0',64);
	scanf("%s",comando);
	while(strcmp(comando,"exit"))
	{
		pid = fork();
		if(pid == 0)
		{
			execlp(comando,comando,NULL);
			printf("Comando não válido");
			exit(0);
		}
		else
		{
			if(pid > 0)
			{
				waitpid(pid, &status, 0);
				printf("MY PROMPT ");
				memset(comando, '\0',64);
				scanf("%s",comando);
			}
			else
				perror("ERROR FORK\n");
		}
	}
	exit(0);
}