/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseed <kseed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 23:27:06 by kseed             #+#    #+#             */
/*   Updated: 2021/04/09 15:47:39 by kseed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_node {
	int             data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_dlink_list {
	size_t	size;
	t_node	*head;
	t_node	*tail;
}	t_dlink_list;

/*
 ----Strings----
 */
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnstr(const char *big, const char *little,
								size_t len);
/*
 ----Memory----
 */
void				*ft_memset(void *s, int c, size_t n);
void				*ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy (void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *arr, int c, size_t n);
/*
 ----is/to----
 */
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(const char *buff, int j);
int					ft_toupper(int c);
int					ft_tolower(int c);
/*
 ----atoi/itoa----
 */
int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);
/*
 ----Str with malloc----
 */
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char *str1, char *str2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
 ----Put fd----
 */
void                ft_putstr(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
 ----List----
 */
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
						void (*del)(void*));
/*
 ----Get next line----
 */
char				*make_line(char *remem);
char				*make_remem(char *remem);
int					get_next_line(int fd, char **line);
int					check_error(int fd, char **remem);
int					ft_free(char *s1, int flag);
int					gnl_end(int byte, char **remem);
/*
 ----Double link list----
 */
void	ft_dlist_del(t_dlink_list **list);
void	*ft_dlist_del_n(t_dlink_list *list, size_t index);
t_node	*ft_dlist_get_n(t_dlink_list *list, size_t index);
void	ft_dlist_insert(t_dlink_list *list, size_t index, int data);
void	*ft_dlist_pop_back(t_dlink_list *list);
void	*ft_dlist_pop_front(t_dlink_list *list);
void	ft_dlist_push_back(t_dlink_list *list, int data);
void	ft_dlist_push_front(t_dlink_list *list, int data);

#endif
