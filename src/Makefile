CC=gcc
CFLAGS = -g -pthread -std=c99 --pedantic -Werror -Wno-implicit-fallthrough -Wall -I includes/ -O2 -pipe -D_FORTIFY_SOURCE=2 -Wno-nonnull-compare -Wextra -D_POSIX_C_SOURCE=200112L 
CLIBRARIES = -lssl -lcrypto
DEPS= $(wildcard includes/*.h)
SRC= $(wildcard *.c)
#OBJ= $(addprefix .objs/, $(SRC:.c=.o))
OBJ=  $(SRC:.c=.o)

TARGET= stegobmp

$(TARGET): $(addprefix .objs/,$(OBJ)) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(addprefix .objs/, $(OBJ)) $(CLIBRARIES) -lm
	@echo "\e[36m[src compiled]\e[0m"

.objs/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -lm
	@echo "\e[32mCompiled object file \e[0m $@"

clean:
	-@rm -rf $(TARGET) .objs/*.o *.o *.out
	@echo "\e[36m[src cleaned]\e[0m"

format:
	clang-format -i -style=google *.c

check:
	cppcheck $(SRC)


.PHONY: clean format check client
