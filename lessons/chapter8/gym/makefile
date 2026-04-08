hfcal.o: hfcal.c
	gcc -I./headers -c hfcal.c -o ./build/hfcal.o
elliptical.o: elliptical.c
	gcc -I./headers -c elliptical.c -o ./build/elliptical.o
hfcal.a: hfcal.c 
	ar -rcs ./build/lib/libhfcal.a ./build/hfcal.o
elliptical: elliptical.c
	gcc ./build/elliptical.o -I./headers -L./build/lib -lhfcal -o ./build/elliptical
