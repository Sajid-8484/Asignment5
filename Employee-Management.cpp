#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Employee {
    int id;
    string name;
    double monthlySalary;
};
double calculateYearlySalary(double monthly) {
    return monthly * 12;
}
void inputEmployees(vector<Employee>& employees, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        Employee emp;
        cout << "\nEmployee " << (i + 1) << " Details:\n";
        cout << "Enter Employee ID: ";
        cin >> emp.id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Name: ";
        getline(cin, emp.name);
        cout << "Enter Monthly Salary: ";
        cin >> emp.monthlySalary;
        employees.push_back(emp);
    }
}

bool writeHighSalaryToFile(vector<Employee>& employees, double threshold) {
    ofstream outFile("high_salary.txt");
    if (!outFile) {
        cout << "Error: Could not open file!\n";
        return false;
    }
    bool found = false;
    outFile << "High Salary Employees Report\n";
    outFile << "============================\n\n";
    for (int i = 0; i < employees.size(); i++) {
        double yearly = calculateYearlySalary(employees[i].monthlySalary);
        if (yearly > threshold) {
            found = true;
            outFile << "Employee ID: " << employees[i].id << endl;
            outFile << "Name: " << employees[i].name << endl;
            outFile << "Monthly Salary: " << employees[i].monthlySalary << endl;
            outFile << "Yearly Salary: " << yearly << endl;
            outFile << "----------------------------\n";
        }
    }
    outFile.close();
    if (!found)
        cout << "\nNo employees exceeded the threshold.\n";
    return true;
}
bool readAndDisplayFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error reading file!\n";
        return false;
    }
    cout << "\n--- Reading from " << filename << " ---\n";
    string line;
    while (getline(inFile, line))
        cout << line << endl;
    inFile.close();
    return true;
}
void displayAllEmployees(const vector<Employee>& employees) {
    cout << "\n--- All Employees ---\n";
    for (int i = 0; i < employees.size(); i++) {
        cout << "ID: " << employees[i].id
             << " | Name: " << employees[i].name
             << " | Monthly Salary: " << employees[i].monthlySalary << endl;
    }
}
int main() {
    vector<Employee> employees;
    int numEmployees;
    double threshold;
    cout << "Enter number of employees: ";
    cin >> numEmployees;
    if (numEmployees <= 0) {
        cout << "Invalid number of employees.\n";
        return 0;
    }
    inputEmployees(employees, numEmployees);
    displayAllEmployees(employees);
    cout << "\nEnter minimum yearly salary threshold: ";
    cin >> threshold;
    if (writeHighSalaryToFile(employees, threshold))
        cout << "\nData saved to high_salary.txt successfully!\n";
    readAndDisplayFile("high_salary.txt");
    return 0;
}
