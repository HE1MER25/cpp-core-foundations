#include <iostream>
using namespace std;
int main() {
    // Age Check Example using if statement
    int age = 25;   
    if (age >= 18) {
        cout << "You are an adult.\n";
    } else {
        cout << "You are a minor.\n";
    }

    // Else-if Example for Grading System
    int score = 85;
    if (score >= 90) {
        cout << "Grade: A\n";
    } else if (score >= 80) {
        cout << "Grade: B\n";
    } else if (score >= 70) {
        cout << "Grade: C\n";
    } else if (score >= 60) {
        cout << "Grade: D\n";
    } else {
        cout << "Grade: F\n\n";
    }

    // Short if...else (Ternary Operator) Example
    int number = 10;
    string result = (number % 2 == 0) ? "Even" : "Odd";
    cout << number << " is " << result << ".\n\n";

    // Nested if Example
    int day = 3; // 1: Monday, 2: Tuesday, ..., 7: Sunday
    if (day >= 1 && day <= 7)
    {
        if (day == 1) {
            cout << "Today is Monday.\n";
        } else if (day == 2) {
            cout << "Today is Tuesday.\n";
        } else if (day == 3) {
            cout << "Today is Wednesday.\n";
        } else if (day == 4) {
            cout << "Today is Thursday.\n";
        } else if (day == 5) {
            cout << "Today is Friday.\n";
        } else if (day == 6) {
            cout << "Today is Saturday.\n";
        } else {
            cout << "Today is Sunday.\n";
        }
    } else {
        cout << "Invalid day number. Please enter a number between 1 and 7.\n";
    }
    return 0;
}