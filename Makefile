# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 01:03:54 by etisha            #+#    #+#              #
#    Updated: 2022/08/04 17:07:57 by sbilli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER = minishell.h

NAME = minishell

MAKEFILE = Makefile

SRC_FILES = cd.c	cd_utils.c	children.c	echo.c	env.c	envp_in_matrix.c \
			execution.c	execution_utils.c	execution_utils2.c	exit.c \
			export.c	export_exam.c	free_memory.c	ft_ascii.c	ft_atoi.c \
			ft_itoa.c	ft_print.c	ft_putstr_fd.c	ft_split.c	ft_strcmp.c \
			ft_strjoin.c	ft_strlen.c	init.c	init_envp_list.c	lexer.c \
			lexer_redirekcs.c	lexer_utils.c	main.c	parser.c	parser_exam.c \
			parser_utils.c	parser_utils2.c	pwd.c	redirect.c	redirect_utils.c \
			run_from_path.c	run_from_path_utils.c	signal.c	term_settings.c \
			unset.c

RL =  -lreadline

OBJ = $(patsubst %.c, %.o, $(SRC_FILES))

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(RL) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER) $(MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
