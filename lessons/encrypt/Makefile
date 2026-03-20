message_hider.o: message_hider.c encrypt.h 
	gcc -c launch.c 

encrypt.o: encrypt.c encrypt.h 
	gcc -c encrypt.c 

message_hider: message_hider.o encrypt.o 
	gcc message_hider.o encrypt.o -o message_hider
