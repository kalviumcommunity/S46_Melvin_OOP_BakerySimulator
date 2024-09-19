#include <iostream>
#include <string>
#include <vector>

class Ingredient
{
private:
    std::string name;
    int quantity;

public:
    Ingredient(const std::string &name, int quantity) : name(name), quantity(quantity) {}

    // Accessors
    std::string getName() const
    {
        return name;
    }
    int getQuantity() const
    {
        return quantity;
    }

    // Mutators
    void setName(const std::string &name)
    {
        this->name = name;
    }
    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }
};

// The BakedGood class abstracts the details of a baked item.
class BakedGood
{
private:
    std::string name;
    static int totalBakedGoods;

public:
    BakedGood(const std::string &name) : name(name)
    {
        totalBakedGoods++;
    }

    // Accessor
    std::string getName() const
    {
        return name;
    }

    // Static Member Functions
    static int getTotalBakedGoods()
    {
        return totalBakedGoods;
    }

    // Public method to display the baking process, demonstrating abstraction by hiding internal details.
    void bake(const std::vector<Ingredient> &ingredients) const
    {
        std::cout << "Baking " << this->name << " with:\n";
        for (const auto &ingredient : ingredients)
        {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n"; // Accessor
        }
        std::cout << "Done baking " << this->name << "!\n";
    }
};

int BakedGood::totalBakedGoods = 0;

// The Customer class abstracts the customer's interaction with baked goods.
class Customer
{
private:
    std::string name;
    static int totalOrders;

public:
    Customer(const std::string &name) : name(name) {}

    // Accessor
    std::string getName() const
    {
        return name;
    }

    void placeOrder(const BakedGood &bakedGood) const
    {
        std::cout << this->name << " ordered a " << bakedGood.getName() << std::endl;
        totalOrders++;
    }

    // Static Memeber functions
    static int getTotalOrders()
    {
        return totalOrders;
    }
};

int Customer::totalOrders = 0;

int main()
{
    std::vector<Ingredient *> Bingredients = {
        new Ingredient("Flour", 100),
        new Ingredient("Sugar", 50),
        new Ingredient("Butter", 30)};

    std::vector<Ingredient *> Pingredients = {
        new Ingredient("Flour", 100),
        new Ingredient("Eggs", 50),
        new Ingredient("Chocolate", 30)};

    BakedGood *bread = new BakedGood("Bread");
    BakedGood *pastry = new BakedGood("Pastry");
    Customer *customer = new Customer("Melvin");

    customer->placeOrder(*bread);
    customer->placeOrder(*pastry);
    
    // Baking goods, showing the use of abstraction as the details of the process are hidden.
    bread->bake({*Bingredients[0], *Bingredients[1], *Bingredients[2]});
    pastry->bake({*Pingredients[0], *Pingredients[1], *Pingredients[2]});

    std::cout << "Total baked goods created: " << BakedGood::getTotalBakedGoods() << std::endl;
    std::cout << "Total orders placed: " << Customer::getTotalOrders() << std::endl;

    delete bread;
    delete pastry;
    delete customer;
    
    for (auto ingredient : Bingredients)
    {
        delete ingredient;
    }
    for (auto ingredient : Pingredients)
    {
        delete ingredient;
    }

    return 0;
}
