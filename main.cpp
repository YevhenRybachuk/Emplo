#include <iostream>
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
        //cout << "Person created: " << name << endl;
    }
    virtual ~Person() {
       // cout << "Person destroyed: " << name << endl;
    }

    virtual void display() const {
        cout << "Name: " << name << endl;
    }
    virtual void work() const {
        cout << name << " is doing general tasks." << endl;
    }
    void staticBindingExample() {
        cout << "I am a Person" << endl;
    }
};

class Employee : public Person, public Workable {
protected:
    string position;
    double salary;
public:
    Employee(string n = "Unknown", string p = "Unknown", double s = 0.0)
        : Person(n), position(p), salary(s) {
       // cout << "Employee created: " << name << endl;
    }
    Employee(const Employee &e) : Person(e.name), position(e.position), salary(e.salary) {
        cout << "Employee copied: " << name << endl;
    }
    virtual ~Employee() {
      //  cout << "Employee destroyed: " << name << endl;
    }

    virtual void display() const override {
        cout << "Employee - Name: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }
    virtual void work() const override {
        cout << name << " is working as " << position << "." << endl;
    }
    virtual void doWork() const override {
        cout << name << "" << endl;
    }
    void staticBindingExample() {
        cout << "I am an Employee" << endl;
    }

    string getName() const { return name; }
    double getSalary() const { return salary; }
};

class Manager : public Employee {
private:
    int teamSize;
public:
    Manager(string n, string p, double s, int t) : Employee(n, p, s), teamSize(t) {
      //  cout << "Manager created: " << name << endl;
    }
    virtual void display() const override {
        cout << "Manager - Name: " << name << ", Position: " << position
             << ", Salary: " << salary << ", Team Size: " << teamSize << endl;
    }
    virtual void work() const override {
        cout << name << " is managing a team of " << teamSize << " people." << endl;
    }
    virtual ~Manager() {
       // cout << "Manager destroyed: " << name << endl;
    }
};

class Intern final : public Person, public Workable {
private:
    string department;
public:
    Intern(string n, string dept) : Person(n), department(dept) {
      //  cout << "Intern created: " << name << " in department " << department << endl;
    }
    virtual void display() const override {
        cout << "Intern - Name: " << name << ", Department: " << department << endl;
    }
    virtual void work() const override final {
        cout << "Intern " << name << " doing small tasks." << endl;
    }
    virtual void doWork() const override {
        cout << "Intern " << name << " is assisting in the " << department << " department" << endl;
    }
    virtual ~Intern() {
      //  cout << "Intern destroyed: " << name << endl;
    }
};

/*class Student : public Intern {
private:
    string faculty;
public:
    Student(string n, string dept, string fac) : Intern(n, dept), faculty(fac) {
        // cout << "Student created: " << name << " in department " << department << ", Faculty: " << faculty << endl;
    }
    virtual void display() const override {
        cout << "Student - Name: " << name << ", Department: " << department << ", Faculty: " << faculty << endl;
    }
    virtual void work() const override final {
        cout << "Student " << name << " is studying and contributing in the " << department << " department." << endl;
    }
    virtual void doWork() const override {
        cout << "Student " << name << " is researching for the " << faculty << " faculty and assisting the " << department << " department." << endl;
    }
    virtual string getRole() const override {
        return "Student";
    }
    virtual ~Student() {
        // cout << "Student destroyed: " << name << endl;
    }
};*/


class Contractor : public Person, public Workable {
private:
    string specialization;
    double hourlyRate;
    int contractDuration;
public:
    Contractor(string n, string spec, double rate, int duration)
        : Person(n), specialization(spec), hourlyRate(rate), contractDuration(duration) {
      //  cout << "Contractor created: " << name << " (Specialization: " << specialization << ")" << endl;
    }
    virtual void display() const override {
        cout << "Contractor - Name: " << name << ", Specialization: " << specialization
             << ", Hourly Rate: $" << hourlyRate << ", Contract Duration: " << contractDuration << " months" << endl;
    }
    virtual void work() const override {
        cout << "Contractor " << name << " is working on a project." << endl;
    }
    virtual void doWork() const override {
        cout << "Contractor " << name << " is completing tasks for the company" << endl;
    }
    virtual ~Contractor() {
      //  cout << "Contractor destroyed: " << name << endl;
    }
};

void performWork(const Workable& worker) {
    worker.doWork();
   }

int main() {
    Employee emp1("Vasya Pupkin", "Software Engineer", 75000);
    emp1.display();

    Manager mgr1("Walter White", "Project Manager", 90000, 10);
    mgr1.display();

    Intern intern1("Dima", "IT");
    intern1.display();

    Contractor contractor1("Alina", "Web Development", 50.0, 6);
    contractor1.display();

    performWork(intern1);
    performWork(contractor1);


    Person* basePtr = new Manager("Sasha", "Lead", 100000, 5);
    basePtr->work();
    delete basePtr;

    Person* p = new Employee("Johnny Sins", "Developer", 50000);
    p->staticBindingExample();
    delete p;

    return 0;
}
