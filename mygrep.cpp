#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <exception>
using namespace std;

// Function to convert a string to lower case
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            string inputString, searchString;

            // Ask user for input
            cout << "Give string from which to search for: ";
            getline(cin, inputString);

            cout << "Give string to search for: ";
            getline(cin, searchString);

            // Look for the string in the input string
            size_t position = inputString.find(searchString);
            if (position != inputString.npos) {
                cout << "\"" << searchString << "\" found in \"" << inputString << "\" in position " << position << endl;
            } else {
                cout << "\"" << searchString << "\" not found in \"" << inputString << "\"" << endl;
            }
        } else if (argc >= 3) {
            string searchString, filename;
            string options = "";
            bool lineNumbering = false;
            bool countOccurrences = false;
            bool reverseSearch = false;
            bool ignoreCase = false;

            // Handle optional argument order
            int argIndex = 1;
            if (argv[argIndex][0] == '-') {
                options = argv[argIndex];
                argIndex++;
            }
            if (argc - argIndex < 2) {
                throw runtime_error("Error: Missing search string or filename");
            }
            searchString = argv[argIndex];
            filename = argv[argIndex + 1];

            // Parse options
            lineNumbering = options.find('l') != string::npos;
            countOccurrences = options.find('o') != string::npos;
            reverseSearch = options.find('r') != string::npos;
            ignoreCase = options.find('i') != string::npos;

            // Try to open the file
            ifstream file(filename);
            if (!file) {
                throw runtime_error("Error: file could not be opened");
            }

            string line;
            int lineNumber = 0;
            int occurrences = 0;
            while (getline(file, line)) {
                lineNumber++;
                string searchLine = line;
                string searchStr = searchString;

                // Convert to lower case if ignoreCase option is set
                if (ignoreCase) {
                    searchLine = toLowerCase(line);
                    searchStr = toLowerCase(searchString);
                }

                // Check if the search string is found in the line
                bool found = searchLine.find(searchStr) != string::npos;
                if (reverseSearch) {
                    found = !found;
                }

                // Print the line if the search string is found (or not found if reverseSearch is set)
                if (found) {
                    if (lineNumbering) {
                        cout << lineNumber << ": ";
                    }
                    cout << line << endl;
                    occurrences++;
                }
            }

            // Print the number of occurrences if countOccurrences option is set
            if (countOccurrences) {
                if (reverseSearch) {
                    cout << "Occurrences of lines NOT containing \"" << searchString << "\": " << occurrences << endl;
                } else {
                    cout << "Occurrences of lines containing \"" << searchString << "\": " << occurrences << endl;
                }
            }
        } else {
            // Print usage information if the arguments are incorrect
            cerr << "Usage: \n" << " ./mygrep (interactive mode) \n" << " ./mygrep [-options] <search> <filename> (search in file)" << endl;
        }
    } catch (const exception& e) {
        // Handle exceptions and print error message
        cerr << "An exception occurred. Exception Nr. -1\n" << e.what() << endl;
    }
    return 0;
}