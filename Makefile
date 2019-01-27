# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/24 17:50:27 by penzo             #+#    #+#              #
#    Updated: 2019/01/27 20:06:41 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC		:= gcc
WFLAGS	:= -Wextra -Wall#-Werror
RM		:= rm -rf

INCL	:= -I includes/ -I libft/
LIBS    := -L libft -lft
SRC		:= minishell.c built_in.c str_utils.c exits.c
SRCS	:= $(addprefix srcs/, $(SRC))
OBJS	:= $(SRCS:.c=.o)
DEPS	:= includes/minishell.h

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
.PHONY: all clean fclean re
