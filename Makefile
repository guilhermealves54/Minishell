# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/04/04 18:20:53 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BULTINS = src/bultins/

SRC = src/

# Srcs
BULTINS_SRCS = echo.c echo2.c \
	export.c export_2.c export_create.c export_syntax.c order_export.c \
	unset.c exec_pwd.c exec_env.c exec_exit.c\
	exec_cd.c cd_utils.c cd_2.c \

OTHER_SRCS = child.c \
	expand.c expand_utils.c execute.c execute2.c \
	ft_printf_fd.c \
	here_doc.c \
	init.c init2.c input.c \
	main.c memclean.c memclean2.c \
	parsing.c parsing_utils.c process.c \
	redir.c redir_utils.c \
	signals.c split_quotes.c split_redir.c \
	utils.c utils2.c

SRCS = $(addprefix $(BULTINS), $(BULTINS_SRCS)) \
	$(addprefix $(SRC), $(OTHER_SRCS))

OBJS = $(SRCS:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Libs
INCLUDES = -I./libft
LIBS = -lreadline -L./libft -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

valgrind: all
	@valgrind --show-below-main=no --leak-check=full --show-leak-kinds=all \
	--track-fds=yes --track-origins=yes --suppressions=rl.supp -s -q ./minishell

.PHONY: all clean fclean re
