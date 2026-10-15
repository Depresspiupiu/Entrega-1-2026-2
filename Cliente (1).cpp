#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlaza la librería Winsock

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // La placa se toma del argumento (Cliente.exe ABC123) o se pide por consola
    std::string placa;
    if (argc > 1) {
        placa = argv[1];
    } else {
        std::cout << "Ingresa la placa: ";
        std::getline(std::cin, placa);
    }
    // El servidor Python lee hasta '\n', así que lo agregamos como delimitador
    std::string mensaje = placa + "\n";

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

    // Convertir dirección IP (inet_pton reemplaza al obsoleto inet_addr)
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
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

    // Enviar la placa
    if (send(sock, mensaje.c_str(), (int)mensaje.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Fallo en send. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    std::cout << "Placa enviada al servidor: " << placa << std::endl;

    // Recibir respuesta (sizeof - 1 para dejar espacio al '\0')
    int valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (valread > 0) {
        buffer[valread] = '\0';
        std::cout << "Respuesta del servidor: " << buffer;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
