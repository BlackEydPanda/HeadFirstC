hfcal.o: hfcal.c
	gcc -I./headers -c hfcal.c -o ./build/hfcal.o
elliptical.o:
	gcc -I./headers -c elliptical.c -o ./build/elliptical.o
hfcal.a: hfcal.o 
	ar -rcs ./build/lib/libhfcal.a ./build/hfcal.o
elliptical: hfcal.o elliptical.o hfcal.a
	gcc ./build/elliptical.o -I./headers -L./build/lib -lhfcal -o ./build/elliptical
