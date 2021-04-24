CC=gcc
CFLAGS= -Wall -Werror

binDir= bin

all:	outputDir my-cat my-grep my-zip my-unzip

outputDir:
	mkdir -p $(binDir)

my-cat:my-cat.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^

my-grep:my-grep.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^

my-zip:my-zip.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^

my-unzip:my-unzip.c
	$(CC) $(CFLAGS) -o $(binDir)/$@ $^

clean:
	rm -r $(binDir)
