CC=gcc
CFLAGS= -Wall -Werror

binDir= bin

all:	outputDir reverse

outputDir:
	mkdir -p $(binDir)

reverse:reverse.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^


clean:
	rm -r $(binDir)