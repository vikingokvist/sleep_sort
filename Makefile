NAME = sleep_sort

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = ./sleep_sort.c ./utils.c ./main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lrt

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS) $(NAME)

re: fclean all
