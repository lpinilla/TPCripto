all:
	@echo "\e[34m[Compiling src]\e[0m"
	cd src;make; cd ..
	@echo "\e[34m[Compiling tests]\e[0m"
	cd tests; make; cd ..
	@cp src/stegobmp bin/stegobmp
	@echo "\e[34m[binary generated at /bin]\e[0m"


clean:
	@cd src; make --no-print-directory clean
	@cd tests; make --no-print-directory clean
	@#@cd Tasteful; make --no-print-directory clean
	@rm -rf bin/*
	-@rm -rf *.out
	@echo "\e[34m[everything cleaned]\e[0m"

format:
	cd src; make format
	cd tests; make format

check:
	cd src; make check
	cd tests; make check

test:
	cd tests; make test

#install_hooks:
#	cp git_hooks/pre-push .git/hooks
#	cd .git/hooks; chmod +x `ls | grep -v '.sample'`

# Build the cscope database.
csclean:
	-rm -vf cscope.out

cscope.out:
	cscope -bvR src/*.c src/includes/*.h

cscope: csclean cscope.out;

.PHONY: cscope csclean test clean format check
