NAME = minishell

SRCS = $(wildcard srcs/*c) $(wildcard srcs/parser/*.c) $(wildcard srcs/execute_part/*.c) $(wildcard srcs/commands/*.c)

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

HEADER = include/minishell.h
LIB = libft/libft.a

INC_DIR = include
LIB_DIR = libft
OBJS_DIR = objs
PARS_DIR = objs/parser
EXEX_DIR = objs/execute_part
COM_DIR = objs/commands

CC = gcc
CFLAGS = -g #-Wall -Werror -Wextra
RM = rm -rf

all: libft $(NAME)

#Здесь надо указать вместо cbilbo свой ник
$(NAME): message $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -L /Users/cbilbo/.brew/opt/readline/lib -I /Users/cbilbo/.brew/opt/readline/include -o $(NAME)
	@echo '√'
	@echo Minishell was created!

$(OBJS): dir $(SRCS) $(HEADER)
	@echo -n '#' 
	@$(CC) $(CFLAGS) -o $@ -c $(@:objs/%.o=srcs/%.c)

libft:
	@$(MAKE) -s -C $(LIB_DIR)

clean:
	@$(MAKE) clean -s -C $(LIB_DIR)
	@echo Objectives deleted
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(LIB) $(NAME)
	@echo 'Minishell deleted('

re: fclean all

message:
	@echo -n 'Create minishell '

dir:
	@mkdir -p $(OBJS_DIR) $(PARS_DIR) $(EXEX_DIR) $(COM_DIR)

.PHONY: all clean fclean re libft message dir