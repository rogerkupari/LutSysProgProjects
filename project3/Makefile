CC=gcc
CFLAGS= -Wall -Werror

binDir= bin

all:	outputDir wish

outputDir:
	mkdir -p $(binDir)

wish:wish.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^


clean:
	rm -r $(binDir)