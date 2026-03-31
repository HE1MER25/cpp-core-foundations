#include <iostream>
using namespace std;
int main() {
    // Boolean Variables
    bool isCodingFun = true;
    bool isFishTasty = false;

    // Output the boolean values
    cout << "Is coding fun? " << isCodingFun << "\n";
    cout << "Is fish tasty? " << isFishTasty << "\n\n";

    // Boolean Expressions
    int a = 10, b = 20;
    bool result1 = (a < b); // true
    bool result2 = (a > b); // false

    cout << "Is a less than b? " << result1 << "\n";
    cout << "Is a greater than b? " << result2 << "\n\n";

    //boolalpha manipulator to print boolean values as true/false
    cout << boolalpha; // Enable boolalpha to print true/false
    cout << "Is a equal to b? " << (a == b) << "\n";
    cout << "Is a not equal to b? " << (a != b) << "\n\n";  

    // Age Check Example using if statement
    int age = 25;   
    if (age >= 18) {
        cout << "You are an adult.\n";
    } else {
        cout << "You are a minor.\n";
    }
    

    return 0;
}