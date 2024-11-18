#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Ingredient {
private:
    std::string name;
    int quantity;

public:
    Ingredient(const std::string& name, int quantity) : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
};

class BakedGood {
private:
    std::string name;
    static int totalBakedGoods;

public:
    // Default constructor
    BakedGood() : name("Generic Baked Good") { ++totalBakedGoods; }

    // Parameterized constructor
    BakedGood(const std::string& name) : name(name) { ++totalBakedGoods; }

    // Destructor
    ~BakedGood() { 
        --totalBakedGoods; 
        std::cout << "BakedGood " << name << " is being destroyed.\n"; 
    }

    std::string getName() const { return name; }
    static int getTotalBakedGoods() { return totalBakedGoods; }

    void bake(const std::vector<Ingredient>& ingredients) const {
        std::cout << "Baking " << name << " with:\n";
        for (const auto& ingredient : ingredients) {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n";
        }
        std::cout << "Done baking " << name << "!\n";
    }
};

int BakedGood::totalBakedGoods = 0;

class Customer {
private:
    std::string name;
    static int totalOrders;

public:
    // Default constructor
    Customer() : name("Anonymous") {}

    // Parameterized constructor
    Customer(const std::string& name) : name(name) {}

    // Destructor
    ~Customer() { 
        std::cout << "Customer " << name << " is being destroyed.\n"; 
    }

    std::string getName() const { return name; }
    void placeOrder(const BakedGood& bakedGood) const {
        std::cout << name << " ordered a " << bakedGood.getName() << "\n";
        ++totalOrders;
    }
    static int getTotalOrders() { return totalOrders; }
};

int Customer::totalOrders = 0;

int main() {
    std::vector<Ingredient> Bingredients = {
        {"Flour", 100},
        {"Sugar", 50},
        {"Butter", 30}
    };

    std::vector<Ingredient> Pingredients = {
        {"Flour", 100},
        {"Eggs", 50},
        {"Chocolate", 30}
    };

    BakedGood bread("Bread");
    BakedGood pastry("Pastry");
    BakedGood defaultBakedGood; // Calls the default constructor

    Customer customer("Melvin");
    Customer defaultCustomer; // Calls the default constructor

    customer.placeOrder(bread);
    customer.placeOrder(pastry);

    bread.bake(Bingredients);
    pastry.bake(Pingredients);

    std::cout << "Total baked goods created: " << BakedGood::getTotalBakedGoods() << "\n";
    std::cout << "Total orders placed: " << Customer::getTotalOrders() << "\n";

    // Explicitly call destructors
    bread.~BakedGood();
    pastry.~BakedGood();
    defaultBakedGood.~BakedGood();
    customer.~Customer();
    defaultCustomer.~Customer();

    return 0;
}