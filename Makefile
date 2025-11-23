NAME = get_next_line.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = /usr/bin/ar rcs
RM = rm -f

SRCS = \
		get_next_line.c \
		get_next_line_utils.c \


BONUS_SRCS = \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

bonus:
		@make OBJS="$(OBJS) $(BONUS_OBJS)" --no-print-directory

#maybe change because of _bonus
%.o: %.c get_next_line.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
