/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:22:51 by hbelle            #+#    #+#             */
/*   Updated: 2024/02/27 15:17:27 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int						ft_strcmp(char *s1, char *s2);
char					*ft_strstr(char *str, char *to_find);
void					ft_swap(int *a, int *b);
void					ft_putnbr_fd(long int nb, int fd);
void					ft_putnbr_fd_unsigned(unsigned long int nb, int fd);
void					ft_putnbr_fd_base_unsigned(unsigned long int nb, int fd,
							char *base);
int						ft_countdigits(int num);
int						ft_countdigits_unsigned(unsigned long int num);
int						ft_countdigits_base_unsigned(unsigned long int nb,
							unsigned int base);
size_t					ft_printf_check(size_t i, const char *format,
							va_list args, size_t *count);
int						ft_printf(const char *format, ...);
char					*get_next_line(int fd);
char					*ft_strdup_gnl(char *buff);
int						ft_checkline(char *str);
char					*ft_strjoin_gnl(char *line, char *buff);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
size_t					ft_strlen(const char *str);
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *dest, const void *src, size_t n);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						ft_atoi(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_strdup(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char *str, char *charset);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

typedef struct s_data
{
	int					i;
	int					count;
	unsigned int		c;
	char				*str;
	unsigned long long	llu;
	char				*base_hex_min;
	char				*base_hex_maj;
	char				*base_decimal;
}						t_data;

int						ft_printf_error(const char *src, ...);
void					ft_putnbr_base(unsigned int nbr, char *base,
							int *count);
void					ft_hexa(unsigned long long nbr, char *base, int *count);
void					ft_u_putnbr_base(unsigned long long nbr, char *base,
							int *count);
void					word_format(const char *src, t_data *data);
void					string_format(va_list param, t_data *data);
void					char_format(va_list param, t_data *data);
void					int_format(va_list param, t_data *data);
void					base_format(va_list param, t_data *data, char *base,
							char form);
int						printf_putstr(char *s);
int						ft_printf(const char *src, ...);

#endif
