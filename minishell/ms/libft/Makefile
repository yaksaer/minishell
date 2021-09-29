# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbilbo <cbilbo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 21:22:34 by cbilbo            #+#    #+#              #
#    Updated: 2021/09/29 14:34:18 by cbilbo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = char/:d_link/:ft_printf/:lists/:memory/:numbers/:print/:string/:utils/

SRCS = $(wildcard char/*.c) $(wildcard d_link/*.c) $(wildcard ft_printf/*.c) \
	$(wildcard lists/*.c) $(wildcard memory/*.c) $(wildcard numbers/*.c) \
	$(wildcard print/*.c) $(wildcard string/*.c) $(wildcard utils/*.c)

OBJS = $(patsubst %.c,objs/%.o,$(SRCS))

HEADER = libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
MLB = ar -rcs

all:
	@echo Create libft
	@$(MAKE) -j4 $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@echo '|'
	@$(MLB) $(NAME) $(OBJS)
	@echo Libft created!

$(OBJS): dir $(SRCS) $(HEADER)
	@echo -n '#'
	@$(CC) $(CFLAGS) -c $(@:objs/%.o=%.c) -o $@

clean:
	@echo Objectives deleted
	@$(RM) objs/

fclean: clean
	@$(RM) $(NAME)
	@echo Libft deleted

re: fclean all

dir:
	@mkdir -p objs/ objs/char/ objs/d_link/ objs/ft_printf/ objs/lists/ objs/memory/ objs/numbers/ objs/print/ objs/string/ objs/utils/
	@echo -n '|'

.PHONY: all clean fclean re dir