#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<cstring>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "product.h"
#include "order.h"

using namespace std;

#define PORT 8080

vector<Product*> load_products(const string& filename) {
    vector<Product*> products;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open " << filename << " for reading.\n";
        return products;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, name, priceStr, attr1, attr2;
        getline(ss, type, '|');
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, attr1, '|');
        getline(ss, attr2, '|');

        try {
            double price = stod(priceStr);
            if (type == "Pastry")
                products.push_back(new Pastry(name, price, attr1, attr2));
            else if (type == "Cake")
                products.push_back(new Cake(name, price, attr1, attr2));
            else if (type == "Bread")
                products.push_back(new Bread(name, price, attr1, attr2));
        } catch (...) {
            cerr << "ERROR: Failed to parse line: " << line << endl;
        }
    }

    return products;
}


void save_product(Product* product, const string& filename) {
    ofstream file(filename, ios::app);
    file << product->to_string() << "\n";
    file.close();
}

string handle_command(const string& command) {
    stringstream ss(command);
    string action;
    getline(ss, action, '|');

    if (action == "ADD_PRODUCT") {
        string type, name, priceStr, attr1, attr2;
        getline(ss, type, '|');
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, attr1, '|');
        getline(ss, attr2, '|');
        double price = stod(priceStr);

        Product* p = nullptr;
        if (type == "Pastry") p = new Pastry(name, price, attr1, attr2);
        else if (type == "Cake") p = new Cake(name, price, attr1, attr2);
        else if (type == "Bread") p = new Bread(name, price, attr1, attr2);

        if (p) {
            save_product(p, "data/products.txt");
            delete p;
            return "SUCCESS: Product added.";
        }
        return "ERROR: Invalid product type.";
    }

    else if (action == "VIEW_PRODUCTS") {
        vector<Product*> products = load_products("data/products.txt");
        if (products.empty()) return "No products found.";

        stringstream out;
        for (auto p : products) {
            out << p->to_string() << "\n";
            delete p;
        }
        return out.str();
    }

    else if (action == "ADD_ORDER") {
        string orderId;
        getline(ss, orderId, '|');

        Order order(orderId);

        while (!ss.eof()) {
            string type, name, priceStr, attr1, attr2;
            getline(ss, type, '|');
            getline(ss, name, '|');
            getline(ss, priceStr, '|');
            getline(ss, attr1, '|');
            getline(ss, attr2, '|');

            double price = stod(priceStr);
            Product* p = nullptr;
            if (type == "Pastry") p = new Pastry(name, price, attr1, attr2);
            else if (type == "Cake") p = new Cake(name, price, attr1, attr2);
            else if (type == "Bread") p = new Bread(name, price, attr1, attr2);
            if (p) order.add_item(p);
        }

        Order::save_order(order, "data/orders.txt");
        return "SUCCESS: Order added.";
    }

    else if (action == "VIEW_ORDERS") {
        vector<Order> orders = Order::load_orders("data/orders.txt");
        if (orders.empty()) return "No orders found.";

        stringstream out;
        for (auto& o : orders) {
         out << o.display_string() << "\n";
            }

        return out.str();
    }

    return "ERROR: Unknown command.";
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    cout << "Server listening on port " << PORT << "...\n";

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            cerr << "Failed to accept connection\n";
            continue;
        }

        cout << "Client connected.\n";

        char buffer[1024] = {0};
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            int valread = read(new_socket, buffer, 1024);
            if (valread <= 0) {
                cout << "[Server] Client disconnected or read failed.\n";
                close(new_socket);
                break;
            }

            string command(buffer);
            string response = handle_command(command);
            send(new_socket, response.c_str(), response.length(), 0);
        }
    }

    close(server_fd);
    return 0;
}
