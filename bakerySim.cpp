#include <iostream>
#include <string>

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

    void setName(const std::string &newName)
    {
        name = newName;
    }
    void setQuantity(int newQuantity)
    {
        quantity = newQuantity;
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

    void bake(const Ingredient &ingredient) const
    {
        std::cout << "Baking " << name << " with " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "..." << std::endl;
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
        std::cout << name << " ordered a " << bakedGood.getName() << std::endl;
    }
};

int main()
{
    Ingredient flour("Flour", 100);
    BakedGood bread("Bread");
    Customer customer("Melvin");

    customer.placeOrder(bread);
    bread.bake(flour);

    return 0;
}
