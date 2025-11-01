#include <iostream>
#include <string>
using namespace std;

// Encapsulation 
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

    double getTotal() { return price * quantity; }
    string getCollection() { return collection; }
};

// Abstraction & Polymorphism 
class Discount {
public:
    virtual double calculate(NFT cart[], int n, double total, bool member, string bank) = 0;
};

//  Inheritance: Different discounts 
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

class LoyaltyDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        return member ? total * 5 / 100 : 0; // 5% for members
    }
};

class BulkDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        return total >= 5 ? 0.5 : 0; // 0.5 ETH off for 5+ ETH
    }
};

class BankDiscount : public Discount {
public:
    double calculate(NFT cart[], int n, double total, bool member, string bank) {
        if(bank != "ABC") return 0;
        double d = total * 15 / 100;
        return d > 2 ? 2 : d; // max 2 ETH discount
    }
};

//  Cart with Encapsulation 
class Cart {
private:
    NFT cart[50];
    int count;

public:
    Cart() { count = 0; }

    void addNFT() {
        cout << "\nEnter NFT details:\n";
        cart[count].input();
        count++;
    }

    double getOriginalTotal() {
        double sum = 0;
        for(int i=0;i<count;i++)
            sum += cart[i].getTotal();
        return sum;
    }

    NFT* getCart() { return cart; }
    int getCount() { return count; }
};

//  Main 
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
    cout << "Original Total: " << total << " ETH" << endl;
    cout << "Discount: " << totalDiscount << " ETH" << endl;
    cout << "Final Total: " << finalTotal << " ETH" << endl;
    cout << "-----------------------\n";

    return 0;
}
