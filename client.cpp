#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

void sendCommand(const std::string& command) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[2048] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    send(sock, command.c_str(), command.length(), 0);
    read(sock, buffer, 2048);
    std::cout << "Server response:\n" << buffer << std::endl;

    close(sock);
}

int main() {
    int choice;
    while (true) {
        std::cout << "\nBakery Inventory Menu:\n";
        std::cout << "1. Add Item\n2. Edit Item\n3. Delete Item\n4. View Inventory\n5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            int qty;
            std::cout << "Enter item name and quantity: ";
            std::cin >> name >> qty;
            sendCommand("add " + name + " " + std::to_string(qty));
        } else if (choice == 2) {
            int id, qty;
            std::cout << "Enter item ID and new quantity: ";
            std::cin >> id >> qty;
            sendCommand("edit " + std::to_string(id) + " " + std::to_string(qty));
        } else if (choice == 3) {
            int id;
            std::cout << "Enter item ID to delete: ";
            std::cin >> id;
            sendCommand("delete " + std::to_string(id));
        } else if (choice == 4) {
            sendCommand("read");
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
