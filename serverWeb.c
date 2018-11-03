/********
** Aluno: Emanuel Queiroz de Albuquerque 11409540
********/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#define PORT 8080

char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html\r\n>"
"<html><head><title>Trabalho 2 LP2</title>\r\n\n"
"<body><center><h1>Funciona!</h1></body>"
"<img src=\"image.jpg\"></center></body></html>\r\n";


int counter;

void* manipula_cliente(void* cli) {
	int cli_socket = (int)cli;
	//char *hello = "Hello from server";
	while(1) {
		char buffer[1024] = {0};
		int valread = read( cli_socket , buffer, 1024);
		if (valread <= 0)
			break;
		printf("[%d] %s\n",++counter, buffer );
		//send(cli_socket , hello , strlen(hello) , 0 );
		send(cli_socket,buffer,strlen(buffer),0);
		//printf("SERVER sent: %s",buffer);

	}
}

int main(int argc, char const *argv[])
{
	pthread_t client_thread;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[2048] = {0};
	int fdimg;

	counter = 0;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT  );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	while (1) /*{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		pthread_create(&client_thread, NULL, manipula_cliente, (void*) new_socket);
	} */
	{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
		{
		//	perror("Erro de conexao!\n");
		//	continue;

		}
		printf("Conectado com Sucesso\n");

		if(fork()){
			close(server_fd);
			memset(buffer, 0, 2048);
			read(client_thread, buffer, 2048);

			printf("%s\n", buffer);

			if(!strncmp(buffer, "GET /image.jpg", 16))
				{
					fdimg = open("image.jpg", O_RDONLY);
					sendfile(client_thread, fdimg, NULL, 21000);
					close(fdimg);
				}

				else
					write(client_thread, webpage, sizeof(webpage) -1);
					close(client_thread);
					exit(0);

		}


	}

	return 0;
}
