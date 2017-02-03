project: hello1.o hello2.o hello3.o hello.o
	gcc hello1.o hello2.o hello3.o hello.o -o project
hello1.o: hello1.c hello.h
	gcc -c hello1.c
hello2.o: hello2.c hello.h
	gcc -c hello2.c
hello3.o: hello3.c hello.h
	gcc -c hello3.c
hello.o: hello.c hello.h
	gcc -c hello.c

