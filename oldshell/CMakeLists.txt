cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS -ltermcap)
add_executable(minishell ./main.c
        minishell.h
        libft/libft.h libft/ft_bzero.c libft/ft_memset.c libft/ft_memcpy.c libft/ft_memccpy.c libft/ft_memmove.c libft/ft_memchr.c libft/ft_memcmp.c
        libft/ft_strlen.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strnstr.c libft/ft_strncmp.c
        libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_strmapi.c
        libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c libft/ft_toupper.c libft/ft_tolower.c
        libft/ft_atoi.c libft/ft_itoa.c
        libft/ft_putchar.c libft/ft_putstr.c libft/ft_putendl.c libft/ft_putnbr.c
        libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c
        libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c libft/ft_lstlast.c libft/ft_lstadd_back.c libft/ft_lstclear.c libft/ft_lstdelone.c
        libft/get_next_line.c libft/ft_strcmp.c libft/DblLinkedList_delete.c libft/DblLinkedList_pushFront.c libft/DblLinkedList_popFront.c
        libft/DblLinkedList_pushBack.c libft/DblLinkedList_popBack.c libft/DblLinkedList_getNthq.c libft/DblLinkedList_insert.c libft/DblLinkedList_deleteNth.c
        libft/ft_isspace.c parser/parser.c libft/free_n_null_ptr.c execute/execute.c exit/exit.c libft/str_is_numeric.c free/free.c)