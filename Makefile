server: server.c
	gcc -Wall server.c -o server
client: client.c
	gcc -Wall client.c -o client
clean:
	@rm -rf server client
