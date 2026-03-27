#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 5;
    // Arithmetic Operators
    // Addition
    cout << "a + b = " << a + b << "\n";

    // Subtraction
    cout << "a - b = " << a - b << "\n";

    // Multiplication
    cout << "a * b = " << a * b << "\n";

    // Division
    cout << "a / b = " << a / b << "\n";

    // Modulus
    cout << "a % b = " << a % b << "\n\n";

    // Increment and Decrement Operators
    cout << "a++ = " << a++ << " (Post-increment)\n";
    cout << "++a = " << ++a << " (Pre-increment)\n";
    cout << "b-- = " << b-- << " (Post-decrement)\n";
    cout << "--b = " << --b << " (Pre-decrement)\n\n";

    int c = 15, d = 20;
    ++c; // Pre-increment: c becomes 16 before being used
    cout << "Pre-increment c: " << c << "\n";
    d++; // Post-increment: d is used as 20, then becomes 21
    cout << "Post-increment d: " << d << "\n\n";
    --c; // Pre-decrement: c becomes 15 before being used
    cout << "Pre-decrement c: " << c << "\n";  
    d--; // Post-decrement: d is used as 21, then becomes 20
    cout << "Post-decrement d: " << d << "\n\n";

    // Assignment Operators
    int e = 10;
    e += 5; // e = e + 5 
    cout << "e += 5: " << e << "\n";
    e -= 3; // e = e - 3
    cout << "e -= 3: " << e << "\n";
    e *= 2; // e = e * 2
    cout << "e *= 2: " << e << "\n";
    e /= 4; // e = e / 4
    cout << "e /= 4: " << e << "\n";
    e %= 3; // e = e % 3
    cout << "e %= 3: " << e << "\n\n";

    int f = 5;
    f |= 3; // f = f | 3 (Bitwise OR)
    cout << "f |= 3: " << f << "\n";
    f &= 2; // f = f & 2 (Bitwise AND)
    cout << "f &= 2: " << f << "\n";
    f ^= 1; // f = f ^ 1 (Bitwise XOR)
    cout << "f ^= 1: " << f << "\n";
    f <<= 1; // f = f << 1 (Left Shift)
    cout << "f <<= 1: " << f << "\n";
    f >>= 1; // f = f >> 1 (Right Shift)
    cout << "f >>= 1: " << f << "\n\n";

    // Comparison Operators
    cout << "a == b: " << (a == b) << "\n";
    cout << "a != b: " << (a != b) << "\n";
    cout << "a > b: " << (a > b) << "\n";
    cout << "a < b: " << (a < b) << "\n";
    cout << "a >= b: " << (a >= b) << "\n";
    cout << "a <= b: " << (a <= b) << "\n\n";

    // Logical Operators
    bool x = true, y = false;
    cout << "x && y: " << (x && y) << "\n";
    cout << "x || y: " << (x || y) << "\n";
    cout << "!x: " << (!x) << "\n";

    return 0;
}   