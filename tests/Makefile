CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c18 -I ../src/includes/ -I ../Tasteful -pthread -Wno-nonnull-compare
CLIBRARIES = -lssl -lcrypto
LIB = testing_suite.c
SOURCES = $(filter-out ../src/main.c, $(wildcard ../src/*.c))
FW = tasteful

TEST_SRC = $(wildcard *.c)
OBJ= $(TEST_SRC:.c=.o)

all: $(TEST_SRC:.c=.tasty) $(FW)
	@echo "\e[36m[Tests ready]\e[0m"

../src/.objs/%.o: ../src/%.c
	@cd ../src/; make --no-print-directory; cd ../tests;

../src/%.c:
	@cd ../src/; make --no-print-directory; cd ../tests;

$(TEST_SRC:.c=.tasty): ../src/.objs/%.o


#generar los ejecutables de las suites
%.tasty: .objs/%.o
	@echo "\e[34mCompiling\e[0m $^"
	$(CC) $(CFLAGS) -o $@ $< ../Tasteful/$(LIB) $(SOURCES) $(CLIBRARIES) -lm
	@echo "\e[32mCompiled\e[0m $@"

.PRECIOUS: .objs/%.o

#armar los .o de los .tasty
.objs/%.o: %.c
	@echo "\e[34mCompiling object files of the tests\e[0m $@"
	$(CC) $(CFLAGS) -c -o $@ $< -lm
	#mv *.o .objs/

$(FW):
	@cd ../Tasteful; make --no-print-directory; cd ../tests; cp ../Tasteful/tasteful .


clean:
	-@rm -rf .objs/*.o *.o *.tasty
	@echo "\e[36m[tests cleaned]\e[0m"

#Corremos la librería sobre los .tasty
test: all
	./tasteful

format:
	clang-format -i -style=google *.c

check:
	cppcheck $(OBJ:=.c)

.PHONY: clean test format src check
