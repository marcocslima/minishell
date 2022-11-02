# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 02:03:37 by acosta-a          #+#    #+#              #
#    Updated: 2022/11/01 23:34:41 by acosta-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Compilation #
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
OPTCC=  -I. -c
RM = rm -rf

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
# SOURCE FILES #
SRC = ./bash.c ./signal.c ./main.c ./utils.c ./utils_two.c ./parser.c \
./export.c ./cd_pwd.c ./exec_and_pipe.c ./echo.c ./echo_utils.c ./echo_utils_two.c \
./exit.c ./cmd_exec.c ./builtin_exec.c ./clean_data.c ./error.c env.c ./here_doc.c \
./redirinput.c rediroutput.c init_scream.c ./redirinput_utils.c \
./clean_error_utils.c ./pipe.c ./utils_main.c ./parser_utils.c ./parser_utils_two.c \
./rediroutput_utils.c

#BONUS =

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:%.c=%.o)

SRC.O = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC.O)
	$(RM) $(NAME)
	make -C ${LIBFT_PATH}
	$(CC) $(CFLAGS) $(SRC.O) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(RM) $(SRC.O)
	make clean -C ${LIBFT_PATH}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${LIBFT_PATH}

re: fclean all
	make clean

debug:
					$(MAKE) -C $(LIBFT_PATH)
					$(CC) -g $(CFLAGS) $(SRC) $(LIBFT) -o $@
					gdb --tui --args ./minishell

.PHONY: clean fclean re
