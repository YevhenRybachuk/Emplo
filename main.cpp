#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n = "Unknown") : name(n) {
        cout << "Person created: " << name << endl;
    }
    virtual ~Person() {
        cout << "Person destroyed: " << name << endl;
    }

    virtual void display() const {
        cout << "Name: " << name << endl;
    }
    virtual void work() const {
        cout << name << " is doing general tasks." << endl;
    }

    void show() const {
        cout << "[Person] Showing: " << name << endl;
    }
};

class Employee : public Person {
protected:
    string position;
    double salary;
    static int employeeCount;
public:
    Employee(string n = "Unknown", string p = "Unknown", double s = 0.0)
        : Person(n), position(p), salary(s) {
        employeeCount++;
        cout << "Employee created: " << name << endl;
    }
    Employee(const Employee &e) : Person(e.name), position(e.position), salary(e.salary) {
        employeeCount++;
        cout << "Employee copied: " << name << endl;
    }
    virtual ~Employee() {
        cout << "Employee destroyed: " << name << endl;
        employeeCount--;
    }
    static int getEmployeeCount() { return employeeCount; }
    virtual void display() const override {
        cout << "Employee - Name: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }

    void work() const override {
        cout << name << " is working as " << position << "." << endl;
    }

    void show() const {
        cout << "[Employee] Showing: " << name << " (Position: " << position << ")" << endl;
    }
    string getName() const { return name; }
    double getSalary() const { return salary; }
};
int Employee::employeeCount = 0;

class Manager : public Employee {
private:
    int teamSize;
public:
    Manager(string n, string p, double s, int t) : Employee(n, p, s), teamSize(t) {
        cout << "Manager created: " << name << endl;
    }
    void display() const override {
        cout << "Manager - Name: " << name << ", Position: " << position
             << ", Salary: " << salary << ", Team Size: " << teamSize << endl;
    }
    void work() const override {
        cout << name << " is managing a team of " << teamSize << " people." << endl;
    }
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

class Intern final : public Employee {
public:
    Intern(string n, string p, double s) : Employee(n, p, s) {
        cout << "Intern created: " << name << endl;
    }
    void display() const final override {
        cout << "Intern - Name: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }
    ~Intern() {
        cout << "Intern destroyed: " << name << endl;
    }
};

// class SeniorIntern : public Intern {
 //public:
   //  SeniorIntern(string n, string p, double s) : Intern(n, p, s) {
     //    cout << "SeniorIntern created: " << name << endl;
     //}
 //};

void showEmployeeDetails(const Employee& emp) {
    emp.display();
}

class Payroll {
private:
    Employee *employee;
    double bonus;
public:
    Payroll(Employee *e, double b = 0.0) : employee(e), bonus(b) {
        cout << "Payroll created for: " << employee->getName() << endl;
    }
    void info() const {
        cout << "Payroll - Employee: " << employee->getName() << ", Salary: "
             << employee->getSalary() << ", Bonus: " << bonus << endl;
    }
    ~Payroll() {
        cout << "Payroll destroyed for: " << employee->getName() << endl;
    }
};

class Department {
private:
    string name;
    vector<Employee*> employees;
public:
    Department(string n = "Unknown") : name(n) {
        cout << "Department created: " << name << endl;
    }
    void addEmployee(Employee* e) {
        employees.push_back(e);
    }
    void details() const {
        cout << "Department: " << name << ", Employees: " << employees.size() << endl;
        for (const auto& e : employees) {
            e->display();
        }
    }
    ~Department() {
        cout << "Department destroyed: " << name << endl;
    }
};

int main() {
    Employee emp1("Vasya Pupkin", "Software Engineer", 75000);
    emp1.display();
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Employee emp2 = emp1;
    emp2.display();
    cout << "Total Employees after copying: " << Employee::getEmployeeCount() << endl;

    Manager mgr1("Walter White", "Project Manager", 90000, 10);
    mgr1.display();

    Payroll payroll1(&emp1, 5000);
    payroll1.info();

    Department dept1("IT Department");
    dept1.addEmployee(&emp1);
    dept1.addEmployee(&mgr1);
    dept1.details();

    Person* p = &emp1;
    p->display();
    p->work();
    p->show();

    Intern intern1("John Doe", "Intern", 20000);
    intern1.display();

    showEmployeeDetails(emp1);
    showEmployeeDetails(mgr1);
    showEmployeeDetails(intern1);

    return 0;
}

