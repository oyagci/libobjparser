NAME	:= libobjparser.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -g3 -I glad/include -I inc/ -L libft/ -lft -I libft/includes -fPIC
LIBS	:=

SRCS	:= \
	src/main.c

OBJS	:= $(SRCS:.c=.o)

# -- Rules --

$(NAME): all

all: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
