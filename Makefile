all:
	gcc -Wall -c claves.c -lrt
	ar -rv libclaves.a claves.o
	gcc -Wall -o cliente1 cliente1.c libclaves.a -lrt
	gcc -Wall -o cliente2 cliente2.c libclaves.a -lrt
	gcc -Wall -o cliente3 cliente3.c libclaves.a -lrt
	gcc -Wall -o cliente4 cliente4.c libclaves.a -lrt
	gcc -Wall -o cliente5 cliente5.c libclaves.a -lrt
	gcc -Wall -o cliente6 cliente6.c libclaves.a -lrt
		gcc -Wall -o servidor servidor.c -pthread -lrt

clean:
	rm -f cliente1
	rm -f cliente2
	rm -f cliente3
	rm -f cliente4
	rm -f cliente5
	rm -f cliente6
	rm -f servidor
	rm -f libclaves.a
	rm -f *.o
