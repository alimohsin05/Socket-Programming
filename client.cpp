#include <iostream>
#include <string>
#include <unistd.h>
#include<cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    cout << "Connected to server.\n";

    while (true) {
        cout << "\n========= Bakery Menu =========\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Add Order\n";
        cout << "4. View Orders\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        string input;

        if (choice == 1) {
            string type, name, attr1, attr2;
            double price;

            cout << "Enter product type (Pastry/Cake/Bread): ";
            getline(cin, type);
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter price: ";
            cin >> price;
            cin.ignore();

            if (type == "Pastry") {
                cout << "Enter filling: ";
                getline(cin, attr1);
                cout << "Enter shape: ";
                getline(cin, attr2);
            } else if (type == "Cake") {
                cout << "Enter flavour: ";
                getline(cin, attr1);
                cout << "Enter frosting: ";
                getline(cin, attr2);
            } else if (type == "Bread") {
                cout << "Enter bread type: ";
                getline(cin, attr1);
                cout << "Enter shape: ";
                getline(cin, attr2);
            } else {
                cout << "Invalid product type.\n";
                continue;
            }

            input = "ADD_PRODUCT|" + type + "|" + name + "|" + to_string(price) + "|" + attr1 + "|" + attr2;
        }

        else if (choice == 2) {
            input = "VIEW_PRODUCTS";
        }

        else if (choice == 3) {
            string orderId, type, name, attr1, attr2;
            double price;
            int count;

            cout << "Enter Order ID: ";
            getline(cin, orderId);
            input = "ADD_ORDER|" + orderId;

            cout << "Enter number of items: ";
            cin >> count;
            cin.ignore();

            for (int i = 0; i < count; i++) {
                cout << "\nItem " << i + 1 << "\n";
                cout << "Type (Pastry/Cake/Bread): ";
                getline(cin, type);
                cout << "Name: ";
                getline(cin, name);
                cout << "Price: ";
                cin >> price;
                cin.ignore();

                if (type == "Pastry") {
                    cout << "Filling: ";
                    getline(cin, attr1);
                    cout << "Shape: ";
                    getline(cin, attr2);
                } else if (type == "Cake") {
                    cout << "Flavour: ";
                    getline(cin, attr1);
                    cout << "Frosting: ";
                    getline(cin, attr2);
                } else if (type == "Bread") {
                    cout << "Bread Type: ";
                    getline(cin, attr1);
                    cout << "Shape: ";
                    getline(cin, attr2);
                }

                input += "|" + type + "|" + name + "|" + to_string(price) + "|" + attr1 + "|" + attr2;
            }
        }

        else if (choice == 4) {
            input = "VIEW_ORDERS";
        }

        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid option.\n";
            continue;
        }

        send(sock, input.c_str(), input.length(), 0);
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        cout << "\nServer: " << buffer << endl;
    }

    close(sock);
    return 0;
}
