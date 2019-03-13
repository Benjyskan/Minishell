# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 19:58:18 by penzo             #+#    #+#              #
#    Updated: 2019/03/13 20:21:21 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

CC			:=	gcc
CFLAGS		:=	-Wextra -Wall -Werror
FSA_FLAGS	:=	-pedantic -g3 -O1 -fsanitize=address
VAL_FLAGS	:=	-g

SRC_PATH	:=	srcs
OBJ_PATH	:=	objs
INC_PATH	:=	includes

SRC_NAME	:=	minishell.c built_in.c str_utils.c exits.c env_utils.c \
			prompt.c cd.c free.c cd_errors.c built_in_env.c shlvl.c \
			built_in_echo.c built_in_setenv.c msg.c msg2.c \
			built_in_unsetenv.c cmdline_utils.c strsplit_multi.c \
			expand.c exec.c init_env.c built_in_env_utils.c expand2.c \
			for_the_norm.c
OBJ_NAME	:=	$(SRC_NAME:.c=.o)

SRC			:=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCL		:=	-Iincludes/ -Ilibft
LIB_PATH	:=	-Llibft
LIB_NAME	:=	-lft
LIB			:=	$(LIB_PATH) $(LIB_NAME)

.PHONY: all, clean, fclean, re, norm, fsa, val

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

fsa: $(OBJ)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(LIB) $^ -o $(NAME)
	./$(NAME)

val: $(OBJ)
	$(CC) $(CFLAGS) $(VAL_FLAGS) $(LIB) $^ -o $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
		--show-reachable=no ./$(NAME)

$(NAME): $(OBJ) libft/libft.a Makefile
	$(CC) $(LIB) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

clean:
	$(MAKE) clean -C libft
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	$(MAKE) fclean -C libft
	rm -fv $(NAME)

re:
	fclean all

d: all
	./$(NAME)

norm:
	norminette $(SRC)
	norminette $(INC_PATH)/*.h
