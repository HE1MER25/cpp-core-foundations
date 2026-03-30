#include <iostream>
#include <string>
using namespace std;
int main() {
    // String Initialization
    string str1 = "Hello, World!";
    string str2("Welcome to C++ programming.");
    string str3 = str1 + " " + str2; // Concatenation

    // String concatenation using append
    string str4;
    str4.append("Let's learn C++.");


    // Output the strings
    cout << "String 1: " << str1 << "\n";
    cout << "String 2: " << str2 << "\n";
    cout << "String 3 " << str3 << "\n";
    cout << "String 4: " << str4 << "\n\n";

    // String Length
    cout << "Length of String 1: " << str1.length() << "\n";
    cout << "Length of String 2: " << str2.length() << "\n\n";

    // Accessing Characters
    cout << "First character of String 1: " << str1[0] << "\n";
    cout << "Last character of String 2: " << str2[str2.length() - 1] << "\n\n";

    // Change a character
    str1[7] = 'w'; // Change 'W' to 'w'
    cout << "Modified String 1: " << str1 << "\n\n";

    // Special Characters
    string str5 = "This is a line.\nThis is another line. \& this is a tab:\tEnd of line.";
    cout << "String with Special Characters:\n" << str5 << "\n\n";

    // Substring
    string substr = str3.substr(0, 13); // Extracts "Hello, World!"
    cout << "Substring of Concatenated String: " << substr << "\n\n";

    // String Comparison
    if (str1 == str2) {
        cout << "String 1 and String 2 are equal.\n";
    } else {
        cout << "String 1 and String 2 are not equal.\n";
    }

    // String Input
    string fullName;
    cout << "Enter your full name: ";
    getline(cin, fullName);
    cout << "Hello, " << fullName << "! Welcome to C++ programming.\n\n";

    // Omitting Namespaces
    std::string str6 = "Using std namespace.";
    std::cout << str6 << "\n";

    // C-style strings
    char cstr1[] = "Hello, C-style string!";
    cout << "C-style String: " << cstr1 << "\n";

    return 0;
}