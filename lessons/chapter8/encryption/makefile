encrypt.o: encrypt.c
	gcc -c encrypt.c -o encrypt.o
checksum.o: checksum.c
	gcc -c checksum.c -o checksum.o
libhfsecurity.a: encrypt.o checksum.o
	ar -rcs libhfsecurity.a encrypt.o checksum.o
encryption_test: encryption_test.c libhfsecurity.a
	gcc -I./headers encryption_test.c -lhfsecurity -o encryption_test
