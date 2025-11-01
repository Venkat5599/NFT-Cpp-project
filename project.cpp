#include <iostream>
#include <string>
using namespace std;

// Encapsulation 
class Product {
private:
    string name;
    string category;
    double price;
    int qty;

public:
    void input() {
        cout << "Name: ";
        cin >> name;
        cout << "Category: ";
        cin >> category;
        cout << "Price: ";
        cin >> price;
        cout << "Qty: ";
        cin >> qty;
    }

    double getTotal() { return price * qty; }
    string getCategory() { return category; }
};

// Abstraction & Polymorphism 
class Discount {
public:
    virtual double calculate(Product cart[], int n, double total, bool member, string bank) = 0;
};

//  Inheritance: Different discounts 
class SeasonalDiscount : public Discount {
public:
    double calculate(Product cart[], int n, double total, bool member, string bank) {
        double sum = 0;
        for(int i=0;i<n;i++)
            if(cart[i].getCategory() == "Clothing")
                sum += cart[i].getTotal();
        return sum * 10 / 100;  // 10% Clothing
    }
};

class LoyaltyDiscount : public Discount {
public:
    double calculate(Product cart[], int n, double total, bool member, string bank) {
        return member ? total * 5 / 100 : 0; // 5% for members
    }
};

class BulkDiscount : public Discount {
public:
    double calculate(Product cart[], int n, double total, bool member, string bank) {
        return total >= 1000 ? 100 : 0; // Rs 100 off above 1000
    }
};

class BankDiscount : public Discount {
public:
    double calculate(Product cart[], int n, double total, bool member, string bank) {
        if(bank != "ABC") return 0;
        double d = total * 15 / 100;
        return d > 500 ? 500 : d; // max 500
    }
};

//  Cart with Encapsulation 
class Cart {
private:
    Product cart[50];
    int count;

public:
    Cart() { count = 0; }

    void addProduct() {
        cout << "\nEnter product details:\n";
        cart[count].input();
        count++;
    }

    double getOriginalTotal() {
        double sum = 0;
        for(int i=0;i<count;i++)
            sum += cart[i].getTotal();
        return sum;
    }

    Product* getCart() { return cart; }
    int getCount() { return count; }
};

//  Main 
int main() {
    Cart cart;
    int n;
    cout << "How many products? ";
    cin >> n;

    for(int i=0;i<n;i++)
        cart.addProduct();

    char ch;
    cout << "\nLoyalty member? (y/n): ";
    cin >> ch;
    bool loyalty = (ch=='y'||ch=='Y');

    string bank;
    cout << "Bank name: ";
    cin >> bank;

    double total = cart.getOriginalTotal();

    // Polymorphism: base pointer multiple child objs
    Discount* discounts[4];
    discounts[0] = new SeasonalDiscount();
    discounts[1] = new LoyaltyDiscount();
    discounts[2] = new BulkDiscount();
    discounts[3] = new BankDiscount();

    double totalDiscount = 0;
    for(int i=0;i<4;i++)
        totalDiscount += discounts[i]->calculate(cart.getCart(), cart.getCount(), total, loyalty, bank);

    double finalTotal = total - totalDiscount;

    cout << "\n-----------------------\n";
    cout << "Original Total: " << total << endl;
    cout << "Discount: " << totalDiscount << endl;
    cout << "Final Total: " << finalTotal << endl;
    cout << "-----------------------\n";

    return 0;
}
