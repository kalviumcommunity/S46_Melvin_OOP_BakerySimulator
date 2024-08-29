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

    std::string getName() const
    {
        return name;
    }
    int getQuantity() const
    {
        return quantity;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }
    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }
};

class BakedGood
{
private:
    std::string name;

public:
    BakedGood(const std::string &name) : name(name) {}

    std::string getName() const
    {
        return name;
    }

    void bake(const std::vector<Ingredient> &ingredients) const
    {
        std::cout << "Baking " << this->name << " with:\n";
        for (const auto &ingredient : ingredients)
        {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n";
        }
        std::cout << "Done baking " << this->name << "!";
    }
};

class Customer
{
private:
    std::string name;

public:
    Customer(const std::string &name) : name(name) {}

    std::string getName() const
    {
        return name;
    }

    void placeOrder(const BakedGood &bakedGood) const
    {
        std::cout << this->name << " ordered a " << bakedGood.getName() << std::endl;
    }
};

int main()
{
    std::vector<Ingredient *> ingredients = {
        new Ingredient("Flour", 100),
        new Ingredient("Sugar", 50),
        new Ingredient("Butter", 30)};

    BakedGood *bread = new BakedGood("Bread");
    Customer *customer = new Customer("Melvin");

    customer->placeOrder(*bread);
    bread->bake({*ingredients[0], *ingredients[1], *ingredients[2]});

    delete bread;
    delete customer;
    for (auto ingredient : ingredients)
    {
        delete ingredient;
    }

    return 0;
}
