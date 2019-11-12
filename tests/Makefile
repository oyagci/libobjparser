NAME	:= run_tests
CC		:= gcc
CFLAGS	:= -Wall -Wextra -g3 -I inc/ -L ../libft/ -lft -I ../libft/includes -I ../inc/
LIBS	:= -lcriterion -L ../ -lobjparser -lft

SRCS	:= \
	test_obj_load.c \
	test_obj_parse.c \

OBJS	:= $(SRCS:.c=.o)

# -- Rules --

$(NAME): all

all: $(OBJS)
	make -C ../libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests: all
	./run_tests
