// Form for MSC using cin and cout
#include <iostream>   
using namespace std;
int main() {
    string name, course, previousSchool;
    int age;

    cout << "Enter your name: ";
    getline(cin, name); // Read full name with spaces

    cout << "Enter your age: ";
    cin >> age; // Read age

    cin.ignore(); // Clear the newline character from the input buffer

    cout << "Enter your Area of Specialization: ";
    getline(cin, course); // Read course name with spaces

    cout << "Enter Previous School: ";
    getline(cin, previousSchool); // Read previous school with spaces

    cout << "\nThank you for providing your information!\n";

    cout << "\n--- Student Information ---\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Area of Specialization: " << course << "\n";
    cout << "Previous School: " << previousSchool << "\n";

    return 0;
}
             