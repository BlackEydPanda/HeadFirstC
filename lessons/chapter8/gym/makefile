hfcal.o: hfcal.c
	gcc -I./headers -fPIC -c hfcal.c -o ./build/hfcal.o
elliptical.o:
	gcc -I./headers -c elliptical.c -o ./build/elliptical.o
hfcal.so: hfcal.o 
	sudo gcc -shared ./build/hfcal.o -o /libs/libhfcal.so
elliptical: hfcal.so elliptical.o
	gcc -I/include -c elliptical.c -o ./build/elliptical.o
	gcc ./build/elliptical.o -L/libs -lhfcal -o elliptical
