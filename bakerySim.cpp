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
    std::vector<Ingredient> ingredients = {
        Ingredient("Flour", 100),
        Ingredient("Sugar", 50),
        Ingredient("Butter", 30)
    };

    BakedGood bread("Bread");
    Customer customer("Melvin");

    customer.placeOrder(bread);
    bread.bake(ingredients);

    return 0;
}
