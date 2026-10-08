#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlaza la librería Winsock

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* mensaje = "nuevo mensaje desde el cliente";

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Fallo al inicializar Winsock. Código de error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Fallo en socket. Código de error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir dirección IP
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
	    std::cerr << "Dirección inválida o no soportada" << std::endl;
	    closesocket(sock);
	    WSACleanup();
	    return 1;
	}

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Fallo en connect. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    send(sock, mensaje, strlen(mensaje), 0);
    std::cout << "Mensaje enviado al servidor\n";

    int valread = recv(sock, buffer, 1024, 0);
    if (valread > 0) {
        buffer[valread] = '\0';  // Asegura que el buffer sea un string válido
        std::cout << "Respuesta del servidor: " << buffer << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
