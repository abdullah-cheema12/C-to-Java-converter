#include <iostream>
#include <stdio>
#include <fstream>

using namespace std;

int main() {
    // day 1
    // working making the system for opening the output and input file
    // also add the fucntionality of boiler plate
    ifstream inputFile("input.cpp");
    ofstream outputFile("output.java");

    if (!inputFile.is_open()) {
        cout << "Error: input.cpp not found." << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output.java." << endl;
        return 1;
    }

    return 0;
}
