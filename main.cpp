#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    string position;
    double salary;
public:
    Employee() : Employee("Unknown", "Unknown", 0.0) {}

    Employee(string n) : Employee(n, "Unknown", 0.0) {}

    Employee(string n, string p) : Employee(n, p, 0.0) {}

    Employee(string n, string p, double s) : name(n), position(p), salary(s) {}

    ~Employee() { cout << "Employee destroyed: " << name << endl; }

    void display() const {
        cout << "Name: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }
};

class Payroll {
private:
    string employeeName;
    double baseSalary;
    double bonus;
public:
    Payroll() : Payroll("Unknown", 0.0, 0.0) {}

    Payroll(string n) : Payroll(n, 0.0, 0.0) {}

    Payroll(string n, double s) : Payroll(n, s, 0.0) {}

    Payroll(string n, double s, double b) : employeeName(n), baseSalary(s), bonus(b) {}

    ~Payroll() { cout << "Payroll record destroyed for: " << employeeName << endl; }

    void info() const {
        cout << "Employee: " << employeeName << ", Base Salary: " << baseSalary << ", Bonus: " << bonus << endl;
    }
};

class Department {
private:
    string name;
    int numOfEmployees;
public:
    Department() : Department("Unknown Department", 0) {}

    Department(string n) : Department(n, 0) {}

    Department(string n, int num) : name(n), numOfEmployees(num) {}

    ~Department() { cout << "Department destroyed: " << name << endl; }

    void details() const {
        cout << "Department: " << name << ", Number of Employees: " << numOfEmployees << endl;
    }
};

int main() {
    Employee emp1("John Doe", "Software Engineer", 75000);
    emp1.display();

    Employee emp2("Alice Brown", "Manager");
    emp2.display();

    Employee emp3("Michael Scott");
    emp3.display();

    Payroll payroll1("John Doe", 75000, 5000);
    payroll1.info();

    Payroll payroll2("Alice Brown", 90000);
    payroll2.info();

    Department dept1("IT Department", 50);
    dept1.details();

    Department dept2("HR Department");
    dept2.details();

    return 0;
}
