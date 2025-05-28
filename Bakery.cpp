#include "Bakery.h"
#include <sstream>

std::string Bakery::addInventory(const std::string& name, int quantity) {
    Item newItem{nextId++, name, quantity};
    inventory.push_back(newItem);
    return "Item added: ID = " + std::to_string(newItem.id);
}

std::string Bakery::editInventory(int id, int newQuantity) {
    for (auto& item : inventory) {
        if (item.id == id) {
            item.quantity = newQuantity;
            return "Item updated.";
        }
    }
    return "Item not found.";
}

std::string Bakery::deleteInventory(int id) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->id == id) {
            inventory.erase(it);
            return "Item deleted.";
        }
    }
    return "Item not found.";
}

std::string Bakery::readInventory() {
    std::ostringstream oss;
    if (inventory.empty()) return "Inventory is empty.\n";
    for (const auto& item : inventory) {
        oss << "ID: " << item.id << ", Name: " << item.name << ", Quantity: " << item.quantity << "\n";
    }
    return oss.str();
}
