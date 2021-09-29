NAME = minishell

SRCS = $(wildcard srcs/*c) $(wildcard srcs/parser/*.c)

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

HEADER = include/minishell.h
LIB = libft/libft.a

INC_DIR = include
LIB_DIR = libft
OBJS_DIR = objs
PARS_DIR = objs/parser

CC = gcc
CFLAGS = -g #-Wall -Werror -Wextra
RM = rm -rf

all: libft $(NAME)

$(NAME): message $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo
	@echo minishell was created!

$(OBJS): $(SRCS) $(HEADER)
	@mkdir -p $(OBJS_DIR) $(PARS_DIR)
	@echo -n '#' 
	@$(CC) $(CFLAGS) -o $@ -c $(@:objs/%.o=srcs/%.c)

libft:
	@echo create library
	@$(MAKE) -s -C $(LIB_DIR)

clean:
	@echo delete library
	@$(MAKE) clean -s -C $(LIB_DIR)
	@echo delete objectives
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(LIB) $(NAME)
	@echo 'minishell was deleted('

re: fclean all

message:
	@echo -n 'create minishell '

.PHONY: all clean fclean re libft message