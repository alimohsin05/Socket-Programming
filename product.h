#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Product(string name = "", double price = 0.0) : name(name), price(price) {}
    virtual ~Product() {}

    virtual string get_type() const = 0;
    virtual string to_string() const = 0;

    string get_name() const { return name; }
    double get_price() const { return price; }
};

class Pastry : public Product {
    string filling;
    string shape;

public:
    Pastry(string name, double price, string filling, string shape)
        : Product(name, price), filling(filling), shape(shape) {}

    string get_type() const override { return "Pastry"; }

    string to_string() const override {
        stringstream ss;
        ss << "Pastry|" << name << "|" << price << "|" << filling << "|" << shape;
        return ss.str();
    }
};

class Cake : public Product {
    string flavour;
    string frosting;

public:
    Cake(string name, double price, string flavour, string frosting)
        : Product(name, price), flavour(flavour), frosting(frosting) {}

    string get_type() const override { return "Cake"; }

    string to_string() const override {
        stringstream ss;
        ss << "Cake|" << name << "|" << price << "|" << flavour << "|" << frosting;
        return ss.str();
    }
};

class Bread : public Product {
    string breadType;
    string shape;

public:
    Bread(string name, double price, string breadType, string shape)
        : Product(name, price), breadType(breadType), shape(shape) {}

    string get_type() const override { return "Bread"; }

    string to_string() const override {
        stringstream ss;
        ss << "Bread|" << name << "|" << price << "|" << breadType << "|" << shape;
        return ss.str();
    }
};

#endif
