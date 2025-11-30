import socket
import csv
from datetime import datetime

HOST = "0.0.0.0"   # listen for ESP32 on all interfaces
PORT = 5000        # must match ESP32

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("Server listening on port", PORT)

conn, addr = server.accept()
print("Connected by", addr)

# Create CSV file
filename = f"data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
csv_file = open(filename, "w", newline="")
csv_writer = csv.writer(csv_file)

# Write header row
csv_writer.writerow(["Hand", "Timestamp", "Ax", "Ay", "Az", "Gx", "Gy", "Gz"])

buffer = ""   # buffer to store incomplete packets

while True:
    data = conn.recv(1024)
    if not data:
        break

    buffer += data.decode()

    # Process lines only when '\n' is found
    while "\n" in buffer:
        line, buffer = buffer.split("\n", 1)
        line = line.strip()
        print("Received:", line)

        row = line.split(",")

        # Expect **8 columns** exactly
        if len(row) == 8:
            csv_writer.writerow(row)
            csv_file.flush()   # save immediately
