#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "product.h"

using namespace std;

class Order {
    string orderId;
    vector<Product*> items;

public:
    Order(string orderId = "") : orderId(orderId) {}

    ~Order() {
        for (auto p : items)
            delete p;
    }

    void add_item(Product* product) {
        items.push_back(product);
    }

    string get_id() const {
        return orderId;
    }

    string to_string() const {
        stringstream ss;
        for (auto item : items) {
            ss << orderId << "|" << item->to_string() << "\n";
        }
        return ss.str();
    }

    string display_string() const {
    stringstream ss;
    ss << "Order ID: " << orderId << "\n";
    for (auto item : items) {
        ss << "  - " << item->to_string() << "\n";
    }
    return ss.str();
}


    static vector<Order> load_orders(const string& filename) {
        vector<Order> orders;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string orderId, type, name, priceStr, attr1, attr2;
            getline(ss, orderId, '|');
            getline(ss, type, '|');
            getline(ss, name, '|');
            getline(ss, priceStr, '|');
            getline(ss, attr1, '|');
            getline(ss, attr2, '|');

            double price = stod(priceStr);
            Product* p = nullptr;

            if (type == "Pastry") {
                p = new Pastry(name, price, attr1, attr2);
            } else if (type == "Cake") {
                p = new Cake(name, price, attr1, attr2);
            } else if (type == "Bread") {
                p = new Bread(name, price, attr1, attr2);
            }

            bool found = false;
            for (auto& o : orders) {
                if (o.get_id() == orderId) {
                    o.add_item(p);
                    found = true;
                    break;
                }
            }

            if (!found) {
                Order newOrder(orderId);
                newOrder.add_item(p);
                orders.push_back(newOrder);
            }
        }

        file.close();
        return orders;
    }

    static void save_order(const Order& order, const string& filename) {
        ofstream file(filename, ios::app);
        file << order.to_string();
        file.close();
    }
};

#endif
