#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

class Ingredient {
private:
    std::string name;
    int quantity;

public:
    Ingredient(const std::string& name, int quantity) : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
};

// Base class BakedGood
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
    virtual ~BakedGood() {
        --totalBakedGoods;
        std::cout << "BakedGood [" << name << "] is being destroyed.\n";
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

// Derived class Pastry using single inheritance
class Pastry : public BakedGood {
public:
    Pastry() : BakedGood("Pastry") {}
    void bake(const std::vector<Ingredient>& ingredients) const {
        std::cout << "Baking a special " << getName() << " with extra care!\n";
        BakedGood::bake(ingredients);
    }
};

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
    virtual ~Customer() { 
        std::cout << "Customer [" << name << "] is being destroyed.\n"; 
    }

    std::string getName() const { return name; }
    void placeOrder(const BakedGood& bakedGood) const {
        std::cout << name << " ordered a " << bakedGood.getName() << "\n";
        ++totalOrders;
    }
    static int getTotalOrders() { return totalOrders; }
};

int Customer::totalOrders = 0;

// Derived class BakedItemOrder demonstrating multiple inheritance
class BakedItemOrder : public Customer, public BakedGood {
public:
    BakedItemOrder(const std::string& customerName, const std::string& bakedGoodName)
        : Customer(customerName), BakedGood(bakedGoodName) {}

    void orderAndBake(const std::vector<Ingredient>& ingredients) {
        placeOrder(*this); // Customer places an order for baked good
        bake(ingredients); // Bake the item
    }
};

int main() {
    // Ingredient vectors
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

    // Single inheritance: Pastry inherits from BakedGood
    Customer customer("Melvin");

    // Multiple inheritance: BakedItemOrder inherits from both Customer and BakedGood
    BakedItemOrder order1("Melvin", "Bread");
    BakedItemOrder order2("Melvin", "Pastry");


    order1.orderAndBake(Bingredients); // Using multiple inheritance
    order2.orderAndBake(Pingredients); 

    std::cout << "Total baked goods created: " << BakedGood::getTotalBakedGoods() << "\n";
    std::cout << "Total orders placed: " << Customer::getTotalOrders() << "\n";

    return 0;
}