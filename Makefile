all:
	gcc -Wall -c claves.c -lrt
	ar -rv libclaves.a claves.o
	gcc -Wall -o cliente1 cliente1.c libclaves.a -lrt
	gcc -Wall -o servidor servidor.c -pthread -lrt

clean:
	rm -f cliente
	rm -f servidor
	rm -f libclaves.a
	rm -f *.o