// *******************************************************************************************
// * Title: Course BST DB Manager    |********************************************************
// * Developed by: Ryan Hatch        |********************************************************
// * Developed on: April 16th 2024   |********************************************************
// * Last Updated: April 20th 2024   |********************************************************
// * Version: 4.2.0                  |********************************************************
// *******************************************************************************************
// *******************************************************************************************
// *******************************************************************************************
// * Description: CLI course manager that allows the user to load from a file into a BST db, *
// * prints the loaded contents, and to print the details of a specific entry from the db.   *
// *******************************************************************************************
// * The program reads the course data from a file and stores it in a map.                   *
// * A switch statement was used to allow the user to choose between the options in the CLI. *
// * The program also has error handling to handle invalid options and file errors.          *
// *******************************************************************************************



#include <fstream>                          // Included for file io
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;    

class Course {                          // Class to represent a course
public:
    string courseNumber;              // Course number
    string name;                     // Courses name
    vector<string> prerequisites;   // Prerequisites for the course

    Course() {}                   // The default constructor

    Course(string num, string n, vector<string> prereqs) :  
        courseNumber(num), name(n), prerequisites(prereqs) {}           // Constructor to initialize the course
};

map<string, Course> loadCoursesFromFile(const string& filePath) {     // Function to load courses from a file
    map<string, Course> courses;                                     // Map to store the courses
    ifstream file(filePath);                                        // Read the file
    string line;                                                   // Store each line of the file in this string

    if (!file.is_open()) {                                       // if the file cant be opened
        cout << "Error opening file or file does not exist\n";  // Print this error message; "Error opening file or file does not exist"
        return courses; 
    }

    while (getline(file, line)) {                           // Read each line of the file
        stringstream ss(line);                             // Create a string stream from the line
        string token;   
        vector<string> tokens;

        while (getline(ss, token, ',')) {              // Read each token separated by a comma
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {                                               // If there are at least two tokens
            vector<string> prereqs(tokens.begin() + 2, tokens.end());          // Get the prerequisites
            courses[tokens[0]] = Course(tokens[0], tokens[1], prereqs);       // Add the course to the map
            // Debug output to check what's being loaded
            cout << "Loaded " << tokens[0] << " with prerequisites: ";      // Print the course number
            for (const string& pre : prereqs) cout << pre << " ";          // Print the prerequisites
            cout << endl;
        } else {                                                         // If the line does not have at least two tokens
            cout << "Error in file format for line: " << line << "\n";  // Print error message
        }
    }

    file.close();                                                   // Close the file
    return courses;                                                // Return the map of courses
}

void printCourse(const map<string, Course>& courses, const string& courseNumber) {              // Function to print a course
    auto it = courses.find(courseNumber);                                                      // Find the course in the map
    if (it != courses.end()) {                                                                // If the course is found
        cout << it->second.courseNumber << ", " << it->second.name << "\nPrerequisites: ";   // Print the course number and name
        for (const string& pre : it->second.prerequisites) {                                // Print the prerequisites
            cout << pre << " ";
        }
        cout << "\n";
    } else {                                                                            // If the course is not found
        cout << "Course not found\n";                                                  // Print error message
    }
}

int main() {                                                                        // Main function
    map<string, Course> courses;                                                   // Map to store courses
    string filePath;                                                              // String to store the file path
    int choice;                                                                  // Integer to store the users choice

    cout << "Welcome to the course planner.\n";                                // Print a welcome message; "Welcome to the course planner."
    while (true) {
        cout << "1. Load Data Structure\n";                                  // Loads the data structure from a file. (In this case I am using the included file 'Program_Input.txt' as the file via user input.)
        cout << "2. Print Course List\n";                                   // Prints the list of courses from the data structure
        cout << "3. Print Course\n";                                       // Prints the details of a specific course in the data structure
        cout << "9. Exit\n";                                              // Exits the program
        cout << "What would you like to do? ";                           // Ask the user for their choice
        cin >> choice;

        switch (choice) {                                                       // A switch statement that depends on the user's choice
        case 1:                                                                // If the user chooses '1', then
            cout << "Enter filename: ";                                       // Ask the user for the file name
            cin >> filePath;                                                 // Read the file name
            courses = loadCoursesFromFile(filePath);                        // Load the courses from the file
            break;
        case 2:                                                           // If the user chooses '2', then
            for (const auto& pair : courses) {                           // Iterate through the courses
                cout << pair.first << ", " << pair.second.name << "\n"; // Print the courses loaded from the file; Course number and name
            }
            break;
        case 3:                                                             // If the user chooses '3', then
            cout << "What course do you want to know about? ";             // Ask the user for the course number
            cin >> filePath;                                              // Reading the users input for the course number
            printCourse(courses, filePath);                              // Prints the course details
            break;
        case 9:                                                        // If the user chooses '9', then
            cout << "Thank you for using the course planner!\n";      // Print a thank you message; "Thank you for using the course planner!"
            return 0;                                                // Exit the program
        default:
            cout << "Invalid option.\n";                           // Error handling; If the user chooses an invalid option 
            break;                                                // Print an error message, "Invalid option."
        }
    }

    return 0;                                                 // End of the program; Return 0
}