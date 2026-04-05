encrypt.o: encrypt.c
	gcc -c encrypt.c -o ./build/encrypt.o
checksum.o: checksum.c
	gcc -c checksum.c -o ./build/checksum.o
libhfsecurity.a: encrypt.o checksum.o
	ar -rcs ./build/libhfsecurity.a ./build/encrypt.o ./build/checksum.o
encryption_test: encryption_test.c libhfsecurity.a
	gcc encryption_test.c -I ./build/ -L ./build/ -lhfsecurity -o ./build/encryption_test
