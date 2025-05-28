
#define BAKERY_H
#include <string>
#include <vector>

struct Item {
    int id;
    std::string name;
    int quantity;
};

class Bakery {
private:
    std::vector<Item> inventory;
    int nextId = 1;

public:
    std::string addInventory(const std::string& name, int quantity);
    std::string editInventory(int id, int newQuantity);
    std::string deleteInventory(int id);
    std::string readInventory();
};
