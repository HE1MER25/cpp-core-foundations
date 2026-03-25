#include <iostream>
using namespace std;
int main() {
    //Output with variables
    int myAge = 24;
    string myName = "Ajulo";
    double height = 1.75;
    cout << "My name is " << myName << ", I am " << myAge << " years old and my height is " << height << "m.\n\n";

    // Output with multiple variables 1
    int x = 23, y = 24, z = 25;
    cout << "The sum of x, y, and z is: " << x + y + z << "\n";

    // Output with multiple variables 2
    int a, b, c;
    a = 23; b = 24; c = 25;
    cout << "The sum of a, b, and c is: " << a + b + c << "\n\n";
   

    // Constant variable
    const double PI = 3.14159;
    cout << "The value of Pi is approximately: " << PI << "\n\n";

    // Calculate the area and perimeter of a rectangle
    int length = 5, width = 3;
    int area = length * width;
    int perimeter = 2 * (length + width);
    cout << "For a rectangle with length " << length << " and width " << width << ":\n";
    cout << "Area: " << area << "\n";
    cout << "Perimeter: " << perimeter << "\n";

    return 0;
}