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

        if (line.find("#include") != string::npos || line.find("using namespace std") != string::npos) {
            outputFile << "        // Removed: " << line << endl;
            continue;
        }

        if (line.find("cout <<") != string::npos) {
            string newLine = line;
            int pos = newLine.find("cout <<");
            newLine.replace(pos, 7, "System.out.print(");
            pos = newLine.find("<<");
            while (pos != string::npos) {
                newLine.replace(pos, 2, " + ");
                pos = newLine.find("<<");
            }
            if (newLine.back() == ';') {
                newLine = newLine.substr(0, newLine.size() - 1);
            }
            newLine += ");";
            outputFile << "        " << newLine << endl;
            continue;
        }

        // If line has string declaration
        if (line.find("string ") != string::npos) {
            string newLine = line;
            int pos = newLine.find("string ");
            newLine.replace(pos, 6, "String ");
            outputFile << "        " << newLine << endl;
            continue;
        }

        // Write all other lines directly
        outputFile << "        " << line << endl;
    }

    // Close Java main and class
    outputFile << "    }\n";
    outputFile << "}\n";

    // Close files
    inputFile.close();
    outputFile.close();

    cout << "✅ Conversion complete. Check output.java\n";

    return 0;
}
