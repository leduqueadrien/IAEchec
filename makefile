#option
CFLAGS = -Wall -Wextra -g

SRC = $(wildcard src/*.c) $(wildcard src/Echec/*.c) $(wildcard src/Matrice/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable

bin/executable: $(OBJ)
	@mkdir -p $(@D)
	cc -o $@ $^ $(LIB)
	@echo "executer avec ./bin/executable"

build/%.o: src/%.c
	@mkdir -p $(@D)
	cc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)