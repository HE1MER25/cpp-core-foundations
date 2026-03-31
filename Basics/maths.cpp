#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Basic Mathematical Functions
    double num1 = 16.0, num2 = 5.0;

    // Square root
    cout << "Square root of " << num1 << " is " << sqrt(num1) << "\n";

    // Power
    cout << num2 << " raised to the power of 3 is " << pow(num2, 3) << "\n";

    // Absolute value
    cout << "Absolute value of -7 is " << abs(-7) << "\n";

    // Rounding functions
    double num3 = 3.7;
    cout << "Ceiling of " << num3 << " is " << ceil(num3) << "\n";
    cout << "Floor of " << num3 << " is " << floor(num3) << "\n";
    cout << "Round of " << num3 << " is " << round(num3) << "\n";

    // Trigonometric functions (in radians)
    double angle = M_PI / 4; // 45 degrees in radians
    cout << "Sine of 45 degrees: " << sin(angle) << "\n";
    cout << "Cosine of 45 degrees: " << cos(angle) << "\n";
    cout << "Tangent of 45 degrees: " << tan(angle) << "\n";

    return 0;
}
