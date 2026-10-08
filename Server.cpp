
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlaza la librería Winsock

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int addrlen = sizeof(direccion);
    char buffer[1024] = {0};
    const char* mensaje = "Hola desde el servidor!";

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Fallo al inicializar Winsock. Código de error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Crear socket
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd == INVALID_SOCKET) {
        std::cerr << "Fallo en socket. Código de error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar dirección
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PORT);

    // Asociar socket a dirección
    if (bind(servidor_fd, (struct sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
        std::cerr << "Fallo en bind. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones
    if (listen(servidor_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Fallo en listen. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Esperando conexión en el puerto " << PORT << "...\n";

    // Aceptar conexión
    nuevo_socket = accept(servidor_fd, (struct sockaddr*)&direccion, &addrlen);
    if (nuevo_socket == INVALID_SOCKET) {
        std::cerr << "Fallo en accept. Código de error: " << WSAGetLastError() << std::endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    // Leer mensaje del cliente
    int valread = recv(nuevo_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Mensaje del cliente: " << buffer << std::endl;

        // Enviar mensaje al cliente
        send(nuevo_socket, mensaje, strlen(mensaje), 0);
        std::cout << "Mensaje enviado al cliente\n";
    }

    // Cerrar sockets
    closesocket(nuevo_socket);
    closesocket(servidor_fd);
    WSACleanup();

    return 0;
}
