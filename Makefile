# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/24 17:50:27 by penzo             #+#    #+#              #
#    Updated: 2019/02/19 05:17:41 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#i think i'm not using .o at all

NAME	:=	minishell

CC		:=	gcc
WFLAGS	:=	-Wextra -Wall#-Werror
RM		:=	rm -rf

INCL	:=	-I includes/ -I libft/
LIBS    :=	-L libft -lft
SRC		:=	minishell.c built_in.c str_utils.c exits.c env_utils.c msg.c \
			prompt.c cd.c free.c cd_errors.c built_in_env.c shlvl.c \
			built_in_echo.c

SRCS	:=	$(addprefix srcs/, $(SRC))
OBJS	:=	$(SRCS:.c=.o)
DEPS	:=	includes/minishell.h

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

$(NAME): $(OBJS) libft/libft.a Makefile
	$(CC) $(WFLAGS) $(INCL) $(LIBS) -o $(NAME) $(SRCS)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(WFLAGS) $(INCL)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
	$(RM) a.out

re: fclean all

d:	all
	./$(NAME)

fsa: $(OBJS) libft/libft.a Makefile
	$(CC) $(WFLAGS) -g3 -fsanitize=address $(INCL) $(LIBS) -o $(NAME) $(SRCS)
	#echo "ENV-I!!!!"
	env SHLVL=99 ./$(NAME)

val:
	$(CC) -g $(WFLAGS) $(INCL) $(LIBS) -o $(NAME) $(SRCS)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all env -i toto=ljhsd ./$(NAME)

.PHONY: all clean fclean re
