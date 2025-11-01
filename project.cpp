#include <iostream>
#include <string>
using namespace std;

// ENCAPSULATION: Data hiding with private members
// The NFT class encapsulates data (name, collection, price, quantity)
// and provides controlled access through public methods (input, getTotal, getCollection)
class NFT {
private:
    string name;
    string collection;
    double price;
    int quantity;

public:
    void input() {
        cout << "NFT Name: ";
        cin >> name;
        cout << "Collection: ";
        cin >> collection;
        cout << "Price (ETH): ";
        cin >> price;
        cout << "Quantity: ";
        cin >> quantity;
    }

    // Encapsulation: getters provide controlled access to private data
    double getTotal() { return price * quantity; }
    string getCollection() { return collection; }
};

// ABSTRACTION: Abstract base class defines interface
// The Discount class is abstract (has pure virtual function)
// It hides the implementation details of different discount types
// Child classes must implement the calculate() method
class Discount {
public:
    virtual double calculate(NFT cart[], int n, double total, bool member, string bank) = 0;
};

// INHERITANCE: Different discount types inherit from base Discount class
// Each class extends the Discount base class and implements its own calculate logic

// POLYMORPHISM: SeasonalDiscount overrides the virtual calculate method
// Provides 10% discount on "Limited Edition" NFTs
class SeasonalDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        double sum = 0;
        for(int i=0;i<n;i++)
            if(cart[i].getCollection() == "Limited Edition")
                sum += cart[i].getTotal();
        return sum * 10 / 100;  // 10% Limited Edition NFTs
    }
};

// POLYMORPHISM: LoyaltyDiscount overrides the virtual calculate method
// Provides 5% discount if user is a loyalty member
class LoyaltyDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        return member ? total * 5 / 100 : 0; // 5% for members
    }
};

// POLYMORPHISM: BulkDiscount overrides the virtual calculate method
// Provides 0.5 ETH discount for purchases >= 5 ETH
class BulkDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        return total >= 5 ? 0.5 : 0; // 0.5 ETH off for 5+ ETH
    }
};

// POLYMORPHISM: BankDiscount overrides the virtual calculate method
// Provides up to 2 ETH discount (15% cap) for ABC bank
class BankDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        if(bank != "ABC") return 0;
        double d = total * 15 / 100;
        return d > 2 ? 2 : d; // max 2 ETH discount
    }
};

// ENCAPSULATION: Cart class hides internal cart array
// Private members: cart array and count
// Public methods provide controlled access to add NFTs and get totals
class Cart {
private:
    NFT cart[50];
    int count;

public:
    // Constructor: Initializes the cart
    Cart() { count = 0; }

    // Method to add NFT to cart
    void addNFT() {
        cout << "\nEnter NFT details:\n";
        cart[count].input();
        count++;
    }

    // Encapsulation: Getter method for total
    double getOriginalTotal() {
        double sum = 0;
        for(int i=0;i<count;i++)
            sum += cart[i].getTotal();
        return sum;
    }

    // Encapsulation: Getter methods provide controlled access
    NFT* getCart() { return cart; }
    int getCount() { return count; }
};

// POLYMORPHISM IN ACTION: Main function demonstrates polymorphism
// Base class pointer (Discount*) can point to any derived class object
// Virtual function calculate() is called based on the actual object type
int main() {
    Cart cart;
    int n;
    cout << "How many NFTs to add? ";
    cin >> n;

    for(int i=0;i<n;i++)
        cart.addNFT();

    char ch;
    cout << "\nLoyalty member? (y/n): ";
    cin >> ch;
    bool loyalty = (ch=='y'||ch=='Y');

    string bank;
    cout << "Bank name: ";
    cin >> bank;

    double total = cart.getOriginalTotal();

    // POLYMORPHISM: Array of base class pointers
    // Each pointer can hold address of any derived class object
    // The correct calculate() method is called at runtime (Dynamic Polymorphism)
    Discount* discounts[4];
    discounts[0] = new SeasonalDiscount();
    discounts[1] = new LoyaltyDiscount();
    discounts[2] = new BulkDiscount();
    discounts[3] = new BankDiscount();

    // POLYMORPHISM: Virtual function call
    // Even though discounts[i] is a Discount pointer,
    // the actual calculate() method of the derived class is called
    // This is Runtime (Dynamic) Polymorphism
    double totalDiscount = 0;
    for(int i=0;i<4;i++)
        totalDiscount += discounts[i]->calculate(cart.getCart(), cart.getCount(), total, loyalty, bank);

    double finalTotal = total - totalDiscount;

    cout << "\n-----------------------\n";
    cout << "Original Total: " << total << " ETH" << endl;
    cout << "Discount: " << totalDiscount << " ETH" << endl;
    cout << "Final Total: " << finalTotal << " ETH" << endl;
    cout << "-----------------------\n";

    return 0;
}
