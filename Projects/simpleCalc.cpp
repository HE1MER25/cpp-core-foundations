/* Project: Basic Arithmetic Engine
 * Purpose: First functional implementation of C++ logic patterns.
 * Date: 25 March 2026
 */

#include <iostream>
using namespace std;
int main() {
     // Simple calculator that performs addition, subtraction, multiplication, and division
    double num1, num2;
    cout << "\nEnter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "Addition: " << num1 + num2 << "\n";
    cout << "Subtraction: " << num1 - num2 << "\n";
    cout << "Multiplication: " << num1 * num2 << "\n";  
    if (num2 != 0) {
        cout << "Division: " << num1 / num2 << "\n";
    } else {
        cout << "Division: Cannot divide by zero.\n";
    }

    return 0;
}