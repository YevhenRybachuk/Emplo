#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n = "Unknown") : name(n) {}
    virtual ~Person() {}

    virtual void display() const {
        cout << "Name: " << name << endl;
    }

    void staticBindingExample() {
        cout << "I am a Person" << endl;
    }

    string getName() const { return name; }
};

class Employee : public Person {
protected:
    string position;
    double salary;
public:
    Employee(string n = "Unknown", string p = "Unknown", double s = 0.0)
        : Person(n), position(p), salary(s) {}

    Employee(const Employee &e) : Person(e.name), position(e.position), salary(e.salary) {}

    virtual void display() const override {
        cout << "Employee - Name: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }

    double getSalary() const { return salary; }
    string getPosition() const { return position; }
};

class Intern final : public Person {
private:
    string department;
public:
    Intern(string n, string dept) : Person(n), department(dept) {}
    virtual void display() const override {
        cout << "Intern - Name: " << name << ", Department: " << department << endl;
    }
    string getDepartment() const { return department; }
};

class Contractor : public Person {
private:
    string specialization;
    double hourlyRate;
    int contractDuration;
public:
    Contractor(string n, string spec, double rate, int duration)
        : Person(n), specialization(spec), hourlyRate(rate), contractDuration(duration) {}

    virtual void display() const override {
        cout << "Contractor - Name: " << name << ", Specialization: " << specialization
             << ", Hourly Rate: $" << hourlyRate << ", Contract Duration: " << contractDuration << " months" << endl;
    }

    string getSpecialization() const { return specialization; }
    double getRate() const { return hourlyRate; }
    int getDuration() const { return contractDuration; }
};

vector<Employee> employees;
vector<Intern> interns;
vector<Contractor> contractors;

void logAction(const string& action) {
    ofstream logFile("history.log", ios::app);
    time_t now = time(0);
    logFile << ctime(&now) << ": " << action << endl;
}

void saveEmployeesToFile() {
    ofstream file("employees.txt");
    for (const auto& e : employees) {
        file << e.getName() << "," << e.getPosition() << "," << e.getSalary() << endl;
    }
}

void loadEmployeesFromFile() {
    ifstream file("employees.txt");
    string name, position;
    double salary;
    while (getline(file, name, ',')) {
        getline(file, position, ',');
        file >> salary;
        file.ignore();
        employees.emplace_back(name, position, salary);
    }
}

void saveInternsToFile() {
    ofstream file("interns.txt");
    for (const auto& i : interns) {
        file << i.getName() << "," << i.getDepartment() << endl;
    }
}

void loadInternsFromFile() {
    ifstream file("interns.txt");
    string name, dept;
    while (getline(file, name, ',')) {
        getline(file, dept);
        interns.emplace_back(name, dept);
    }
}

void saveContractorsToFile() {
    ofstream file("contractors.txt");
    for (const auto& c : contractors) {
        file << c.getName() << "," << c.getSpecialization() << "," << c.getRate() << "," << c.getDuration() << endl;
    }
}

void loadContractorsFromFile() {
    ifstream file("contractors.txt");
    string name, spec;
    double rate;
    int duration;
    while (getline(file, name, ',')) {
        getline(file, spec, ',');
        file >> rate;
        file.ignore();
        file >> duration;
        file.ignore();
        contractors.emplace_back(name, spec, rate, duration);
    }
}

void addEmployee() {
    string name, position;
    double salary;
    cout << "Enter name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter position: ";
    getline(cin, position);
    cout << "Enter salary: ";
    cin >> salary;
    employees.emplace_back(name, position, salary);
    saveEmployeesToFile();
    logAction("Admin added an employee");
}

void addIntern() {
    string name, department;
    cout << "Enter name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter department: ";
    getline(cin, department);
    interns.emplace_back(name, department);
    saveInternsToFile();
    logAction("Admin added an intern");
}

void addContractor() {
    string name, specialization;
    double rate;
    int duration;
    cout << "Enter name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter specialization: ";
    getline(cin, specialization);
    cout << "Enter hourly rate: ";
    cin >> rate;
    cout << "Enter contract duration (months): ";
    cin >> duration;
    contractors.emplace_back(name, specialization, rate, duration);
    saveContractorsToFile();
    logAction("Admin added a contractor");
}

void removeEmployee() {
    string name;
    cout << "Enter name of employee to remove: ";
    cin.ignore(); getline(cin, name);
    auto it = remove_if(employees.begin(), employees.end(), [name](const Employee& e) { return e.getName() == name; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        saveEmployeesToFile();
        logAction("Admin removed an employee");
        cout << "Employee removed.\n";
    } else {
        cout << "Employee not found.\n";
    }
}

void removeIntern() {
    string name;
    cout << "Enter name of intern to remove: ";
    cin.ignore(); getline(cin, name);
    auto it = remove_if(interns.begin(), interns.end(), [name](const Intern& i) { return i.getName() == name; });
    if (it != interns.end()) {
        interns.erase(it, interns.end());
        saveInternsToFile();
        logAction("Admin removed an intern");
        cout << "Intern removed.\n";
    } else {
        cout << "Intern not found.\n";
    }
}

void removeContractor() {
    string name;
    cout << "Enter name of contractor to remove: ";
    cin.ignore(); getline(cin, name);
    auto it = remove_if(contractors.begin(), contractors.end(), [name](const Contractor& c) { return c.getName() == name; });
    if (it != contractors.end()) {
        contractors.erase(it, contractors.end());
        saveContractorsToFile();
        logAction("Admin removed a contractor");
        cout << "Contractor removed.\n";
    } else {
        cout << "Contractor not found.\n";
    }
}

void viewAllInterns() {
    for (const auto& i : interns) i.display();
    logAction("User viewed all interns");
}

void viewAllContractors() {
    for (const auto& c : contractors) c.display();
    logAction("User viewed all contractors");
}

void viewHistory() {
    ifstream logFile("history.log");
    string line;
    while (getline(logFile, line)) cout << line << endl;
}

void adminMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Employee\n2. Add Intern\n3. Add Contractor\n";
        cout << "4. Remove Employee\n5. Remove Intern\n6. Remove Contractor\n";
        cout << "7. View All Employees\n8. View All Interns\n9. View All Contractors\n";
        cout << "10. View History\n11. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: addIntern(); break;
            case 3: addContractor(); break;
            case 4: removeEmployee(); break;
            case 5: removeIntern(); break;
            case 6: removeContractor(); break;
            case 7: for (auto& e : employees) e.display(); break;
            case 8: viewAllInterns(); break;
            case 9: viewAllContractors(); break;
            case 10: viewHistory(); break;
            case 11: cout << "Logging out.\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 11);
}

void userMenu() {
    int choice;
    do {
        cout << "\nUser Menu:\n";
        cout << "1. View All Employees\n.";
        cout << "2. View All Interns\n3. View All Contractors\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: for (auto& e : employees) e.display(); logAction("User viewed all employees"); break;
            case 2: viewAllInterns(); break;
            case 3: viewAllContractors(); break;
            case 4: break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 5);
}

void loginMenu() {
    int choice;
    string password;
    do {
        cout << "\nLogin as:\n1. Admin\n2. User\n3. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter admin password: ";
                cin >> password;
                if (password == "2134") adminMenu();
                else cout << "Wrong password.\n";
                break;
            case 2: userMenu(); break;
            case 3: cout << "Exiting.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

int main() {
    loadEmployeesFromFile();
    loadInternsFromFile();
    loadContractorsFromFile();
    loginMenu();
    return 0;
}
