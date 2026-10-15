import socket
import re
import threading

HOST = "0.0.0.0"   # Escucha en todas las interfaces (equivale a INADDR_ANY)
PORT = 8080

# Formatos de placa colombiana
PATRON_CARRO = re.compile(r"^[A-Z]{3}\d{3}$")        # ABC123
PATRON_MOTO = re.compile(r"^[A-Z]{3}\d{2}[A-Z]$")    # ABC12D


def analizar_placa(placa: str) -> str:
    """Analiza la placa y devuelve la respuesta que se enviará al cliente."""
    placa = placa.strip().upper()

    if PATRON_CARRO.match(placa):
        return f"OK|{placa}|Vehiculo (carro)"
    if PATRON_MOTO.match(placa):
        return f"OK|{placa}|Motocicleta"
    return f"ERROR|{placa}|Formato de placa invalido"


def atender_cliente(conn: socket.socket, addr):
    print(f"[+] Conexión de {addr[0]}:{addr[1]}")
    try:
        # TCP es un flujo de bytes: leemos hasta encontrar el '\n'
        datos = b""
        while b"\n" not in datos:
            fragmento = conn.recv(1024)
            if not fragmento:
                break
            datos += fragmento

        if not datos:
            return

        placa = datos.decode("utf-8", errors="ignore").split("\n")[0]
        print(f"Placa recibida: {placa.strip()}")

        respuesta = analizar_placa(placa)
        conn.sendall((respuesta + "\n").encode("utf-8"))
        print(f"Respuesta enviada: {respuesta}")
    except ConnectionError as e:
        print(f"[!] Error con el cliente {addr}: {e}")
    finally:
        conn.close()


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as servidor:
        # Permite reiniciar el servidor sin esperar a que se libere el puerto
        servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        servidor.bind((HOST, PORT))
        servidor.listen(5)
        print(f"Esperando conexiones en el puerto {PORT}... (Ctrl+C para salir)")

        try:
            while True:
                conn, addr = servidor.accept()
                # Un hilo por cliente para poder atender varios a la vez
                threading.Thread(
                    target=atender_cliente, args=(conn, addr), daemon=True
                ).start()
        except KeyboardInterrupt:
            print("\nServidor detenido.")


if __name__ == "__main__":
    main()
