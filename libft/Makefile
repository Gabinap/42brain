NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = /usr/bin/ar rcs
RM = rm -f

SRCS = \
        ft_printf.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

%.o: %.c ft_printf.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
