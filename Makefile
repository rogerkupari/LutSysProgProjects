

all:
	make -C project1
	make -C project2
	make -C project3

clean: 
	make -C project1 clean
	make -C project2 clean
	make -C project3 clean