.PHONY: all run exec debug clean cleanall

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
GCH = $(SRC:.c=.gch)
EXEC = exe
CFLAGS += -Wall -Wextra -Wvla -Wall -Wextra -Werror -pedantic --std=c17
LINK += -lm

all: run

run: $(EXEC)
	./$(EXEC)

exec: $(EXEC)

$(EXEC): $(OBJ) $(LINK)
	gcc -o $@ $^ $(CFLAGS)
	@echo "Compilation terminée."

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)
