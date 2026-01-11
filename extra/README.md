Для Linux
g++ -std=c++17 server.cpp -o server
g++ -std=c++17 client.cpp -o client

g++ -std=c++17 -lrt sender.cpp -o sender
g++ -std=c++17 -lrt receiver.cpp -o receiver

g++ -std=c++17 -lrt writer.cpp -o writer
g++ -std=c++17 -lrt reader.cpp -o reader

g++ -std=c++17 server_socket.cpp -o server_socket
g++ -std=c++17 client_socket.cpp -o client_socket

Далее в двух разных терминалах:
./server
./client

./sender
./receiver

./writer
./reader

./server_socket
./client_socket
