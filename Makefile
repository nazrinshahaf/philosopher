NAME := philo

CC := gcc
CFLAGS := -Wall -Wextra -Werror
TFLAGS := -lpthread
AR := ar rcs
RM := rm -f

PHILOSOPHERS_SRC := src

SRC_FILES := $(wildcard $(PHILOSOPHERS_SRC)/*.c)

PHILOSOPHERS_MAIN := ./philo.c

$(NAME): ./philo.c
	$(CC) $(TFLAGS) $(SRC_FILES) $(PHILOSOPHERS_MAIN) -o $(NAME)

all: $(NAME)

run: all
	./philo 3 100 100 100 5

3: all
	./philo 3 100 100 100 5

4: all
	./philo 4 100 100 100 5

5: all
	./philo 5 100 100 100 5

n: all
	./philo 5 800 200 200

n2: all
	./philo 4 410 200 200

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all run clean
