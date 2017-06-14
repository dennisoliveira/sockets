/* Headers básicos */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int Meusocket;
	struct sockaddr_in vitima;
	int Conector;
	int porta = 80;

	// Validação de argumentos
	/*if (argv[1] <= 0 || argv[1] == NULL) {
		printf("Error Port\n: Não foi informado o valor da porta\n");
		exit(1);
	} else {
		porta = atoi(argv[1]);
	}*/

	Meusocket = socket(AF_INET, SOCK_STREAM, 0); // Função que inicia o socket, definindo tipo, tipo de transporte TCP ou UDP e protocolo
	/* Aqui faz-se uma simples checagem de erro */
	if (Meusocket < 0) {
		perror("Error Socket\n");
		exit(1);
	}

	vitima.sin_family = AF_INET; // Família ou tipo de socket
	vitima.sin_port = htons(porta); // Porta
	vitima.sin_addr.s_addr = inet_addr("127.0.0.1"); // Endereço IP do host
	bzero(&(vitima.sin_zero), 8); // Informação adicional

	//Testar a comunicação e iniciar processo de comunicação com servidor (socket, struct socket e tamanho da estrutura)
	Conector = connect(Meusocket, (struct sockaddr * )&vitima, sizeof(vitima));
	/* Mais uma checagem de erro */
	if (Conector < 0) {
		perror("Error Connect\n");
		exit(1);
	}

	printf("\nConexão realizada com sucesso\n: A porta %d está aberta.\n\n", porta);

	// Requisição
	char req[] = "GET /socket.html HTTP/1.1\r\nhost: localhost\r\n\r\n"; //socket.html
	send(Meusocket, req, strlen(req), 0); // Envia requisição

	printf("Requisição:\n%s\n", req);

	char buffer[512]; // Buffer para armazenar dados 0x200

	int bytes = 1; // Bytes recebidos

	printf("Resposta:\n");
	// Enquanto estiver recebendo
	while(bytes > 0) {
		memset(buffer, 0, 512); // Limpa o buffer 0x200 0x0
		bytes = recv(Meusocket, buffer, 512, 0); // Recebe dados 0x200
		printf("%s", buffer); // Mostra-os
	}

	printf("\n\nDados recebidos, fechando a conexão\n\n");

	close(Meusocket);

	return 0;

}
