#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Ingredient {
private:
    std::string name;
    int quantity;
public:
    Ingredient(const std::string &name, int quantity) : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void reduceQuantity(int amount) { quantity -= amount; }
    void addQuantity(int amount) { quantity += amount; }
};

class Inventory {
private:
    std::unordered_map<std::string, int> stock;
public:
    void addIngredient(const Ingredient &ingredient) {
        stock[ingredient.getName()] += ingredient.getQuantity();
    }
    bool useIngredient(const std::string &name, int amount) {
        if (stock[name] >= amount) {
            stock[name] -= amount;
            return true;
        }
        return false;
    }
    void displayStock() const {
        std::cout << "Current Inventory:\n";
        for (const auto &item : stock) {
            std::cout << "- " << item.first << ": " << item.second << "g\n";
        }
    }
};

class Recipe {
private:
    std::string bakedGoodName;
    std::vector<Ingredient> ingredients;
public:
    Recipe(const std::string &name, const std::vector<Ingredient> &ingredients) 
        : bakedGoodName(name), ingredients(ingredients) {}
    std::string getBakedGoodName() const { return bakedGoodName; }
    const std::vector<Ingredient>& getIngredients() const { return ingredients; }
};

//Base Class as a Common Interface
class BakedGood {
private:
    std::string name;
    static int totalBakedGoods;
public:
    BakedGood(const std::string &name) : name(name) { ++totalBakedGoods; }
    virtual ~BakedGood() { --totalBakedGoods; }
    std::string getName() const { return name; }
    static int getTotalBakedGoods() { return totalBakedGoods; }
    virtual void bake(const std::vector<Ingredient> &ingredients) const = 0;
};
int BakedGood::totalBakedGoods = 0;

//Derived Class Substitutability
class Pastry : public BakedGood {
public:
    Pastry() : BakedGood("Pastry") {}
    void bake(const std::vector<Ingredient> &ingredients) const override {
        std::cout << "Baking a special " << getName() << " with the following ingredients:\n";
        for (const auto &ingredient : ingredients) {
            std::cout << "- " << ingredient.getQuantity() << "g of " << ingredient.getName() << "\n";
        }
    }
};

//Derived Class Substitutability
class Cake : public BakedGood {
public:
    Cake() : BakedGood("Cake") {}
    void bake(const std::vector<Ingredient> &ingredients) const override {
        std::cout << "Baking a lovely " << getName() << " with the following ingredients:\n";
        for (const auto &ingredient : ingredients) {
            std::cout << "- " << ingredient.getQuantity() << "g of " << ingredient.getName() << "\n";
        }
    }
};

class Customer {
private:
    std::string name;
public:
    Customer(const std::string &name) : name(name) {}
    std::string getName() const { return name; }
};

class Order {
private:
    Customer customer;
    std::shared_ptr<BakedGood> bakedGood;
    std::vector<Ingredient> ingredients;
public:
    Order(const Customer &customer, std::shared_ptr<BakedGood> bakedGood, const std::vector<Ingredient> &ingredients) 
        : customer(customer), bakedGood(bakedGood), ingredients(ingredients) {}
    void processOrder() const {
        std::cout << customer.getName() << " ordered a " << bakedGood->getName() << "\n";
        bakedGood->bake(ingredients);
    }
};

class Feedback {
private:
    std::vector<std::string> feedbackList;
public:
    void addFeedback(const std::string &feedback) {
        feedbackList.push_back(feedback);
    }
    void displayFeedback() const {
        std::cout << "Customer Feedback:\n";
        for (const auto &feedback : feedbackList) {
            std::cout << "- " << feedback << "\n";
        }
    }
};

int main() {
    Inventory inventory;
    inventory.addIngredient({"Flour", 500});
    inventory.addIngredient({"Sugar", 200});
    inventory.addIngredient({"Butter", 100});

    Recipe pastryRecipe("Pastry", {{"Flour", 100}, {"Sugar", 50}, {"Butter", 30}});
    std::shared_ptr<BakedGood> pastry = std::make_shared<Pastry>();

    Customer customer("Melvin");
    Order order(customer, pastry, pastryRecipe.getIngredients());

    std::cout << "Processing Order...\n";
    bool sufficientStock = true;
    for (const auto &ingredient : pastryRecipe.getIngredients()) {
        if (!inventory.useIngredient(ingredient.getName(), ingredient.getQuantity())) {
            std::cout << "Not enough " << ingredient.getName() << " in stock.\n";
            sufficientStock = false;
        }
    }

    if (sufficientStock) {
        inventory.displayStock();
        Feedback feedback;
        feedback.displayFeedback();
        order.processOrder();
        feedback.addFeedback("Delicious pastry!");
    } else {
        std::cout << "Order cannot be processed due to insufficient ingredients.\n";
    }


    std::cout << "Total baked goods: " << BakedGood::getTotalBakedGoods() << "\n";
    return 0;
}