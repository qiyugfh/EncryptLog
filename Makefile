SRC = main.c config.h aes.h aes.c log.h log.c md5.h md5.c
test: $(SRC)
	gcc -O0 -g -Wall -o $@ $^

.PHONY: clean
clean:
	-rm test *.log
