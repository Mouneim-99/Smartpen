import socket

HOST = "0.0.0.0"   # listen for any device
PORT = 5000        # must match ESP32 port

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("Server listening on port", PORT)

conn, addr = server.accept()
print("Connected by", addr)

while True:
    data = conn.recv(1024)
    if not data:
        break
    print(data.decode(), end="")
