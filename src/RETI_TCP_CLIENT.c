#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define BUFFER_SIZE 512
#define PORT		27015

void ClearWinSock();

int main(void) {

#ifdef WIN32
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		fprintf(stderr, "Error at WSAStartup()\n");
		return EXIT_FAILURE;
	}
#endif

	// Creazione socket
	int clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		fprintf(stderr, "Socket creation failed.\n");
		ClearWinSock();
		return EXIT_FAILURE;
	}

	// Costruzione indirizzo server
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(PORT);

	// Connessione al server
	if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
		fprintf(stderr, "Failed to connect.\n");
		ClearWinSock();
		return EXIT_SUCCESS;
	}

	char buffer[128];
	if (recv(clientSocket, buffer, sizeof(buffer), 0) != sizeof(buffer)) {
		fprintf(stderr, "recv() failed.\n");
		closesocket(clientSocket);
		ClearWinSock();
		return EXIT_SUCCESS;
	}
	printf("\n%s\n", buffer);

	char str1[128];
	char str2[128];
	printf("Inserisci la prima stringa: ");
	scanf("%s", str1);
	printf("Inserisci la seconda stringa: ");
	scanf("%s", str2);

	if (send(clientSocket, str1, sizeof(str1), 0) < 0) {
		fprintf(stderr, "send() failed.\n");
		closesocket(clientSocket);
		ClearWinSock();
		return EXIT_SUCCESS;
	}

	if (send(clientSocket, str2, sizeof(str2), 0) < 0) {
		fprintf(stderr, "send() failed.\n");
		closesocket(clientSocket);
		ClearWinSock();
		return EXIT_SUCCESS;
	}

	if (recv(clientSocket, str1, sizeof(str1), 0) != sizeof(str1)) {
		fprintf(stderr, "recv() failed.\n");
		closesocket(clientSocket);
		ClearWinSock();
		return EXIT_SUCCESS;
	}

	if (recv(clientSocket, str2, sizeof(str2), 0) != sizeof(str2)) {
		fprintf(stderr, "recv() failed.\n");
		closesocket(clientSocket);
		ClearWinSock();
		return EXIT_SUCCESS;
	}

	printf("\nStringa 1: %s\nStringa 2: %s", str1, str2);
	closesocket(clientSocket);
	ClearWinSock();

	return EXIT_SUCCESS;
}

void ClearWinSock() {
#ifdef WIN32
	WSACleanup();
#endif
}
