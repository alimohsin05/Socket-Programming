#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>
#include "Bakery.h"

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[2048] = {0};

    Bakery bakery;

   //TCP Socket bannay ka code ye 4 lines hain mainly
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is running... at port: " << PORT << std::endl;

    while (true) {
        std::cout << "\n[Server] Waiting for a client...\n";
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        std::cout << "[Server] Client connected.\n";

        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(new_socket, buffer, 2048);
        if (bytesRead <= 0) {
            std::cerr << "[Server] Read failed or client disconnected.\n";
            close(new_socket);
            continue;
        }

        std::cout << "[Server] Received: " << buffer << "\n";

        std::istringstream iss(buffer);
        std::string command;
        iss >> command;

        std::string response;

        if (command == "add") {
            std::string name;
            int qty;
            iss >> name >> qty;
            response = bakery.addInventory(name, qty);
        } else if (command == "edit") {
            int id, qty;
            iss >> id >> qty;
            response = bakery.editInventory(id, qty);
        } else if (command == "delete") {
            int id;
            iss >> id;
            response = bakery.deleteInventory(id);
        } else if (command == "read") {
            response = bakery.readInventory();
        } else {
            response = "Invalid command.";
        }

        send(new_socket, response.c_str(), response.length(), 0);
        std::cout << "[Server] Response sent.\n";
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
