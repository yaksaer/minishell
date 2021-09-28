NAME = minishell

SRCS = minishell.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

HEADER = include/minishell.h
LIB = ./libft/libft.a

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
INC_DIR = ./include
LIB_DIR = ./libft

CC = gcc
#CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf

all: libft $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) $(HEADER_B)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I $(LIB_DIR) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $(<:.c=.o)

libft:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft