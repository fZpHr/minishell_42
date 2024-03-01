# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 17:52:23 by hbelle            #+#    #+#              #
#    Updated: 2024/02/27 15:18:54 by hbelle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_countdigits_base_unsigned.c \
	ft_countdigits_unsigned.c \
	ft_countdigits.c ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_printf_check.c \
	ft_printf.c\
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd_base_unsigned.c \
	ft_putnbr_fd_unsigned.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	get_next_line_utils.c \
	get_next_line.c \
	ft_strstr.c \
	ft_strcmp.c \
	ft_swap.c \
	printf_format.c \
	printf_putstr.c \
	printf_utilis.c \
	printf.c \

OBJTS	=	${SRCS:.c=.o} 

CC	=	cc
RM	=	rm -f

CFLAGS = -Wall -Wextra -Werror -g

.c.o:
	@${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}

$(NAME): ${OBJTS}
		ar rcs ${NAME} ${OBJTS}
		@echo "\033[01m\033[4;33mCompilation done\033[00m\033[1;31m:\033[00m\033[1;32m ${NAME}\033[00m"
		
all:	${NAME}
	@echo "\033[01m\033[31mLinking ...\033[00m"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
	@echo "\033[01m\033[32mCompilation done => ${NAME}\033[00m"
clean:
	@${RM} ${OBJTS}
	@echo "\033[01m\033[31mRemoving objects ...\033[00m"

fclean:	clean
	@${RM} ${NAME}
	@echo "\033[01m\033[31mRemoving exec : ${NAME} ...\033[00m"

re:	fclean all

.PHONY: all clean fclean re
