#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Order {
    int orderID;
    string customerName;
    int itemCount;
    double itemPrice;
};

double calculateTotalBill(int items, double price) {
    return items * price;
}
int getPositiveInt(const string& message) {
    int value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Error: Enter a positive integer!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }
    return value;
}
double getPositiveDouble(const string& message) {
    double value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Error: Enter a positive number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }
    return value;
}
void inputOrders(vector<Order>& orders, int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        Order ord;
        cout << "\nOrder " << (i + 1) << " Details:\n";
        cout << "Enter Order ID: ";
        cin >> ord.orderID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Customer Name: ";
        getline(cin, ord.customerName);
        ord.itemCount = getPositiveInt("Enter Number of Items: ");
        ord.itemPrice = getPositiveDouble("Enter Price per Item: ");
        orders.push_back(ord);
    }
}
bool writePriorityOrdersToFile(const vector<Order>& orders, double threshold) {
    ofstream outFile("priority_orders.txt");
    if (!outFile) {
        cout << "Error creating file!\n";
        return false;
    }
    bool found = false;
    outFile << "Priority Orders Report\n";
    outFile << "======================\n\n";
    for (const auto& ord : orders) {
        double total = calculateTotalBill(ord.itemCount, ord.itemPrice);
        if (total > threshold) {
            found = true;
            outFile << "Order ID: " << ord.orderID << endl;
            outFile << "Customer Name: " << ord.customerName << endl;
            outFile << "Items: " << ord.itemCount << endl;
            outFile << "Price per Item: " << ord.itemPrice << endl;
            outFile << "Total Bill: " << total << endl;
            outFile << "-------------------------\n";
        }
    }
    outFile.close();
    if (!found)
        cout << "\nNo priority orders found.\n";
    return true;
}
bool readAndDisplayFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!\n";
        return false;
    }
    cout << "\n--- Displaying " << filename << " ---\n";
    string line;
    while (getline(inFile, line))
        cout << line << endl;
    inFile.close();
    return true;
}
void displayAllOrders(const vector<Order>& orders) {
    cout << "\n--- All Orders ---\n";
    for (const auto& ord : orders) {
        cout << "Order ID: " << ord.orderID
             << " | Customer: " << ord.customerName
             << " | Total Bill: "
             << calculateTotalBill(ord.itemCount, ord.itemPrice)
             << endl;
    }
}
int main() {
    vector<Order> orders;
    int numOrders;
    double priorityThreshold;
    cout << "Enter total number of orders: ";
    cin >> numOrders;
    if (numOrders <= 0) {
        cout << "Invalid number of orders!\n";
        return 0;
    }
    inputOrders(orders, numOrders);
    displayAllOrders(orders);
    cout << "\nEnter minimum bill amount for priority orders: ";
    cin >> priorityThreshold;
    if (writePriorityOrdersToFile(orders, priorityThreshold))
        cout << "\nPriority orders saved successfully!\n";
    readAndDisplayFile("priority_orders.txt");
    return 0;
}
