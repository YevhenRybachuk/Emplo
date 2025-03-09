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

    friend ostream& operator<<(ostream& os, const Employee& e) {
        os << "Name: " << e.name << ", Position: " << e.position << ", Salary: " << e.salary;
        return os;
    }

    friend istream& operator>>(istream& is, Employee& e) {
        cout << "Enter name: ";
        is >> e.name;
        cout << "Enter position: ";
        is >> e.position;
        cout << "Enter salary: ";
        is >> e.salary;
        return is;
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

    friend ostream& operator<<(ostream& os, const Payroll& p) {
        os << "Employee: " << p.employeeName << ", Base Salary: " << p.baseSalary << ", Bonus: " << p.bonus;
        return os;
    }

    friend istream& operator>>(istream& is, Payroll& p) {
        cout << "Enter employee name: ";
        is >> p.employeeName;
        cout << "Enter base salary: ";
        is >> p.baseSalary;
        cout << "Enter bonus: ";
        is >> p.bonus;
        return is;
    }

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

    friend ostream& operator<<(ostream& os, const Department& d) {
        os << "Department: " << d.name << ", Number of Employees: " << d.numOfEmployees;
        return os;
    }

    friend istream& operator>>(istream& is, Department& d) {
        cout << "Enter department name: ";
        is >> d.name;
        cout << "Enter number of employees: ";
        is >> d.numOfEmployees;
        return is;
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
    cout << emp1 << endl;
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Payroll payroll1("John Doe", 75000, 5000);
    cout << payroll1 << endl;

    Department dept1("IT Department", 50);
    cout << dept1 << endl;
    cout << "Total Departments: " << Department::getTotalDepartments() << endl;

    Employee emp2;
    cin >> emp2;
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Payroll payroll2;
    cin >> payroll2;

    Department dept2;
    cin >> dept2;
    cout << "Total Departments: " << Department::getTotalDepartments() << endl;

    cout << emp2 << endl;
    cout << payroll2 << endl;
    cout << dept2 << endl;

    Employee empcopy = emp1;
    empcopy.display();

    Payroll payrollcopy = payroll1;
    payrollcopy.info();

    Department deptcopy = dept1;
    deptcopy.details();

    return 0;
}

