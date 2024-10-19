PROGRAM := philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

INCDIR = inc
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm $(PROGRAM)

re: fclean all

ifeq ($(MAKECMDGOALS), debug)
CFLAGS += $(DEBUGFLAGS)
endif

debug: re

.PHONY: all clean fclean re debug