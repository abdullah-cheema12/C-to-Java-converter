#include <iostream>
#include <stdio>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Open input and output files
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

    // Start Java class and main method
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

        // If line has cout
        if (line.find("cout <<") != string::npos) {
            string newLine = line;
            // Replace 'cout <<' with 'System.out.print('
            int pos = newLine.find("cout <<");
            newLine.replace(pos, 7, "System.out.print(");

            // Replace '<<' with '+'
            pos = newLine.find("<<");
            while (pos != string::npos) {
                newLine.replace(pos, 2, " + ");
                pos = newLine.find("<<");
            }

            // Remove semicolon and close print statement
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

        // For all other lines, just write them directly
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
