#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

class Ingredient
{
private:
    std::string name;
    int quantity;

public:
    Ingredient(const std::string &name, int quantity) : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
};

// Base class BakedGood (Abstract Class)
class BakedGood
{
private:
    std::string name;
    static int totalBakedGoods;

public:
    BakedGood() : name("Generic Baked Good") { ++totalBakedGoods; }
    BakedGood(const std::string &name) : name(name) { ++totalBakedGoods; }

    virtual ~BakedGood()
    {
        --totalBakedGoods;
        std::cout << "BakedGood [" << name << "] is being destroyed.\n";
    }

    std::string getName() const { return name; }
    static int getTotalBakedGoods() { return totalBakedGoods; }

    // Pure virtual function
    virtual void bake(const std::vector<Ingredient> &ingredients) const = 0;
};

int BakedGood::totalBakedGoods = 0;

// Derived class Pastry using single inheritance
class Pastry : public BakedGood
{
public:
    Pastry() : BakedGood("Pastry") {}

    void bake(const std::vector<Ingredient> &ingredients) const override
    {
        std::cout << "Baking a special " << getName() << " with extra care!\n";
        for (const auto &ingredient : ingredients)
        {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n";
        }
        std::cout << "Done baking " << getName() << "!\n";
    }
};

class Customer
{
private:
    std::string name;
    static int totalOrders;

public:
    Customer() : name("Anonymous") {}
    Customer(const std::string &name) : name(name) {}

    virtual ~Customer()
    {
        std::cout << "Customer [" << name << "] is being destroyed.\n";
    }

    std::string getName() const { return name; }
    void placeOrder(const BakedGood &bakedGood) const
    {
        std::cout << name << " ordered a " << bakedGood.getName() << "\n";
        ++totalOrders;
    }
    static int getTotalOrders() { return totalOrders; }
};

int Customer::totalOrders = 0;

// Derived class BakedItemOrder demonstrating multiple inheritance
class BakedItemOrder : public Customer, public BakedGood
{
public:
    BakedItemOrder(const std::string &customerName, const std::string &bakedGoodName)
        : Customer(customerName), BakedGood(bakedGoodName) {}

    void bake(const std::vector<Ingredient> &ingredients) const override
    {
        std::cout << "Baking a custom order for " << BakedGood::getName() << ":\n";
        for (const auto &ingredient : ingredients)
        {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n";
        }
        std::cout << "Done baking " << BakedGood::getName() << "!\n";
    }

    void orderAndBake(const std::vector<Ingredient> &ingredients)
    {
        Customer::placeOrder(*this); // Specify Customer's placeOrder
        bake(ingredients);           // Bake the item
    }
};

int main()
{
    std::vector<Ingredient> Bingredients = {
        {"Flour", 100},
        {"Sugar", 50},
        {"Butter", 30}};

    std::vector<Ingredient> Pingredients = {
        {"Flour", 100},
        {"Eggs", 50},
        {"Chocolate", 30}};

    Customer customer("Melvin");

    BakedItemOrder order1("Melvin", "Bread");
    BakedItemOrder order2("Melvin", "Pastry");

    std::unique_ptr<BakedGood> pastry = std::make_unique<Pastry>();
    pastry->bake(Pingredients);

    order1.orderAndBake(Bingredients);
    order2.orderAndBake(Pingredients);

    std::cout << "Total baked goods created: " << BakedGood::getTotalBakedGoods() << "\n";
    std::cout << "Total orders placed: " << Customer::getTotalOrders() << "\n";

    return 0;
}
