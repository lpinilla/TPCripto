CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -I ../src/includes/ -I ../Tasteful -pthread -Wno-nonnull-compare
LIB = testing_suite.c
SOURCES = $(filter-out ../src/main.c, $(wildcard ../src/*.c))
FW = tasteful

TEST_SRC = $(wildcard *.c)
OBJ= $(addprefix .objs/, $(TEST_SRC:.c=.o))

all: src $(TEST_SRC:.c=.tasty) $(FW)
	@echo "\e[36m[Tests ready]\e[0m"

src:
	@cd ../src/; make --no-print-directory; cd ../tests;

#generar los ejecutables de las suites
$(TEST_SRC:.c=.tasty): $(OBJ)
	@echo "\e[34mCompiling\e[0m $^"
	$(CC) $(CFLAGS) -o $@ $(OBJ) ../Tasteful/$(LIB) $(SOURCES)
	@echo "\e[32mCompiled\e[0m $@"

#armar los .o de los .tasty
$(OBJ): $(TEST_SRC)
	@echo "\e[34mCompiling object files of the tests\e[0m $@"
	$(CC) -c $< $(CFLAGS) $(SOURCES)
	mv *.o .objs/

$(FW):
	@cd ../Tasteful; make --no-print-directory; cd ../tests; cp ../Tasteful/tasteful .


clean:
	-@rm -rf .objs/*.o *.tasty
	@echo "\e[36m[tests cleaned]\e[0m"

#Corremos la librería sobre los .tasty
test: all
	./tasteful

format:
	clang-format -i -style=google *.c

check:
	cppcheck $(OBJ:=.c)

.PHONY: clean test format src check
