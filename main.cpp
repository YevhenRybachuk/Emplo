#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    string position;
    double salary;
    static int employeeCount;
public:
    Employee() : Employee("Unknown", "Unknown", 0.0) {}

    Employee(string n) : Employee(n, "Unknown", 0.0) {}

    Employee(string n, string p) : Employee(n, p, 0.0) {}

    Employee(string n, string p, double s) : name(n), position(p), salary(s) {
        employeeCount++;
    }

    Employee(const Employee &e) : name(e.name), position(e.position), salary(e.salary) {
        cout << "Employee copied: " << this->name << endl;
        employeeCount++;
    }

    ~Employee() {
        cout << "Employee destroyed: " << this->name << endl;
        employeeCount--;
    }

    void display() const {
        cout << "Name: " << this->name << ", Position: " << this->position << ", Salary: " << this->salary << endl;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }
};

int Employee::employeeCount = 0;

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

    Payroll(const Payroll &p) : employeeName(p.employeeName), baseSalary(p.baseSalary), bonus(p.bonus) {
        cout << "Payroll copied for: " << this->employeeName << endl;
    }

    ~Payroll() { cout << "Payroll record destroyed for: " << this->employeeName << endl; }

    void info() const {
        cout << "Employee: " << this->employeeName << ", Base Salary: " << this->baseSalary << ", Bonus: " << this->bonus << endl;
    }
};

class Department {
private:
    string name;
    int numOfEmployees;
    static int totalDepartments;
public:
    Department() : Department("Unknown Department", 0) {}

    Department(string n) : Department(n, 0) {}

    Department(string n, int num) : name(n), numOfEmployees(num) {
        totalDepartments++;
    }

    Department(const Department &d) : name(d.name), numOfEmployees(d.numOfEmployees) {
        cout << "Department copied: " << this->name << endl;
        totalDepartments++;
    }

    ~Department() {
        cout << "Department destroyed: " << this->name << endl;
        totalDepartments--;
    }

    void details() const {
        cout << "Department: " << this->name << ", Number of Employees: " << this->numOfEmployees << endl;
    }

    static int getTotalDepartments() {
        return totalDepartments;
    }
};

int Department::totalDepartments = 0;

int main() {
    Employee emp1("John Doe", "Software Engineer", 75000);
    emp1.display();
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Employee emp2("Alice Brown", "Manager");
    emp2.display();
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

   // Employee emp3("Michael Scott");
    //emp3.display();
    //cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Employee empCopy = emp1;
    empCopy.display();
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Payroll payroll1("John Doe", 75000, 5000);
    payroll1.info();

    Payroll payroll2("Alice Brown", 90000);
    payroll2.info();

    Payroll payrollCopy = payroll1;
    payrollCopy.info();

    Department dept1("IT Department", 50);
    dept1.details();
    cout << "Total Departments: " << Department::getTotalDepartments() << endl;

    Department dept2("HR Department");
    dept2.details();
    cout << "Total Departments: " << Department::getTotalDepartments() << endl;

    Department deptCopy = dept1;
    deptCopy.details();
    cout << "Total Departments: " << Department::getTotalDepartments() << endl;

    return 0;
}

