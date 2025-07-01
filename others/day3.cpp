#include <iostream>
#include <stdio>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.cpp");
    ofstream outputFile("output.java");

    if (!inputFile.is_open() || !outputFile.is_open()) return 1;

    outputFile << "public class ConvertedProgram {\n";
    outputFile << "    public static void main(String[] args) {\n";

    string line;
    while (getline(inputFile, line)) {

        // If line has #include, write comment and continue
        if (line.find("#include") != string::npos) {
            outputFile << "        // Removed: " << line << endl;
            continue;
        }

        // If line has using namespace std, write comment and continue
        if (line.find("using namespace std") != string::npos) {
            outputFile << "        // Removed: " << line << endl;
            continue;
        }
    }

    return 0;
}
