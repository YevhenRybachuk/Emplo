#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Workable {
public:
    virtual void doWork() const = 0;
    virtual ~Workable() {}
};

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

    virtual string getRole() const = 0;
};

class Employee : public Person, public Workable {
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
    virtual void work() const override {
        cout << name << " is working as " << position << "." << endl;
    }
    virtual void doWork() const override {
        cout << name << " is actively performing work tasks!" << endl;
    }
    virtual string getRole() const override {
        return "Employee";
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
    virtual void display() const override {
        cout << "Manager - Name: " << name << ", Position: " << position
             << ", Salary: " << salary << ", Team Size: " << teamSize << endl;
    }
    virtual void work() const override {
        cout << name << " is managing a team of " << teamSize << " people." << endl;
    }
    virtual string getRole() const override {
        return "Manager";
    }
    virtual ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

class Intern final : public Person, public Workable {
private:
    string department;
public:
    Intern(string n, string dept) : Person(n), department(dept) {
        cout << "Intern created: " << name << " in department " << department << endl;
    }
    virtual void display() const override {
        cout << "Intern - Name: " << name << ", Department: " << department << endl;
    }
    virtual void work() const override final {
        cout << "Intern " << name << " is learning and doing small tasks." << endl;
    }
    virtual void doWork() const override {
        cout << "Intern " << name << " is assisting in the " << department << " department!" << endl;
    }
    virtual string getRole() const override {
        return "Intern";
    }
    virtual ~Intern() {
        cout << "Intern destroyed: " << name << endl;
    }
};

// class SeniorIntern : public Intern {
//public:
//  SeniorIntern(string n, string p, double s) : Intern(n, p, s) {
//    cout << "SeniorIntern created: " << name << endl;
//}
//};

class Contractor : public Person, public Workable {
private:
    string specialization;
    double hourlyRate;
    int contractDuration;
public:
    Contractor(string n, string spec, double rate, int duration)
        : Person(n), specialization(spec), hourlyRate(rate), contractDuration(duration) {
        cout << "Contractor created: " << name << " (Specialization: " << specialization << ")" << endl;
    }
    virtual void display() const override {
        cout << "Contractor - Name: " << name << ", Specialization: " << specialization
             << ", Hourly Rate: $" << hourlyRate << ", Contract Duration: " << contractDuration << " months" << endl;
    }
    virtual void work() const override {
        cout << "Contractor " << name << " is working on a temporary project." << endl;
    }
    virtual void doWork() const override {
        cout << "Contractor " << name << " is completing freelance tasks for the company!" << endl;
    }
    virtual string getRole() const override {
        return "Contractor";
    }
    virtual ~Contractor() {
        cout << "Contractor destroyed: " << name << endl;
    }
};

void performWork(const Workable& worker) {
    worker.doWork();
}

int main() {
    Employee emp1("Vasya Pupkin", "Software Engineer", 75000);
    emp1.display();
    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    Manager mgr1("Walter White", "Project Manager", 90000, 10);
    mgr1.display();

    Intern intern1("Johnny", "IT");
    performWork(intern1);
    intern1.display();

    Contractor contractor1("Alice", "Web Development", 50.0, 6);
    performWork(contractor1);
    contractor1.display();

    cout << emp1.getName() << " is an " << emp1.getRole() << endl;
    cout << mgr1.getName() << " is a " << mgr1.getRole() << endl;
    cout << intern1.getRole() << " is an Intern" << endl;
    cout << contractor1.getRole() << " is a Contractor" << endl;

    return 0;
}


