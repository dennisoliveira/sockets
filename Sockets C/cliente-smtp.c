/* Headers básicos */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int socket_i;
	struct sockaddr_in host;
	int conexao;
	int porta = 25;

	socket_i = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_i < 0) {
		perror("Error Socket\n");
		exit(1);
	}

	host.sin_family      = AF_INET;
	host.sin_port        = htons(porta);
	host.sin_addr.s_addr = inet_addr("69.163.253.9");
	bzero(&(host.sin_zero), 8);

	conexao = connect(socket_i, (struct sockaddr *) &host, sizeof(host));

	if (conexao < 0) {
		perror("Error Connect\n");
		exit(1);
	}

	printf("\nConexão realizada com sucesso\n: A porta %d está aberta.\n\n", porta);

	char buffer[1024]; // Buffer para armazenar dados 0x200
	int bytes = 1; // Bytes recebidos

	// Resposta
	printf("Resposta:\n");
	memset(buffer, 0, 1024); // Limpa o buffer
	bytes = recv(socket_i, buffer, 1024, 0);
	printf("%s", buffer);

	// Requisição
	char req[] = "quit\r\n";
	send(socket_i, req, strlen(req), 0); // Envia requisição
	printf("\nRequisição:\n%s", req);

	// Resposta
	printf("\nResposta:\n");
	memset(buffer, 0, 1024); // Limpa o buffer
	bytes = recv(socket_i, buffer, 1024, 0);
	printf("%s\n", buffer);

	/*// Requisição
	strcpy(req, "quit\r\n");
	send(socket_i, req, strlen(req), 0); // Envia requisição
	printf("\nRequisição:\n%s\n", req);

	// Resposta
	printf("\nResposta:\n");
	memset(buffer, 0, 512); // Limpa o buffer
	bytes = recv(socket_i, buffer, 512, 0);
	printf("%s", buffer);

	printf("\n\nDados recebidos, fechando a conexão\n\n");*/

	close(socket_i);

	return 0;

}
