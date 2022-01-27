NAME := philo_bonus

CC := gcc
CFLAGS := -Wall -Wextra -Werror
TFLAGS := -lpthread
AR := ar rcs
RM := rm -f

PHILOSOPHERS_BONUS_SRC := src

SRC_FILES := $(wildcard $(PHILOSOPHERS_BONUS_SRC)/*.c)

PHILOSOPHERS_BONUS_MAIN := ./philo_bonus.c

$(NAME): $(PHILOSOPHERS_BONUS_MAIN)
	$(CC) $(TFLAGS) $(SRC_FILES) $(PHILOSOPHERS_BONUS_MAIN) -o $(NAME)

all: $(NAME)

run: all
	./philo 3 100 100 100 5

4live: all
	./philo 4 410 200 200 5

4die: all
	./philo 4 310 210 100

5live: all
	./philo 5 800 200 200 

5livel: all
	./philo 5 800 200 200 7

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all run clean
