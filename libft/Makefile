# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 21:22:34 by cbilbo            #+#    #+#              #
#    Updated: 2021/10/22 19:50:43 by cbilbo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = char/:d_link/:ft_printf/:lists/:memory/:numbers/:print/:string/:utils/

SRCS = $(wildcard char/*.c) $(wildcard d_link/*.c) $(wildcard ft_printf/*.c) \
	$(wildcard lists/*.c) $(wildcard memory/*.c) $(wildcard numbers/*.c) \
	$(wildcard print/*.c) $(wildcard string/*.c) $(wildcard utils/*.c)

OBJS = $(patsubst %.c,%.o,$(SRCS))

HEADER = libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
MLB = ar -rcs

all: dir
	@echo Create libft
	@$(MAKE) -s -j4 $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(MLB) $(NAME) $(OBJS)
	@echo '√'
	@echo Libft created!

%.o: %.c $(HEADER)
	@echo -n '#'
	@$(CC) $(CFLAGS) -c $< -o $@
# $(OBJS): $(SRCS) $(HEADER)
# 	@echo -n '#'
# 	@$(CC) $(CFLAGS) -c $(@:objs/%.o=%.c) -o $@

clean:
	@echo Objectives deleted
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo Libft deleted

re: fclean all

.PHONY: all clean fclean re dir