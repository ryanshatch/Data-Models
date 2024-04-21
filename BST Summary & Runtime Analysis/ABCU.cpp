#include <fstream>  // For file input and output.
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;    

class Course {                          // Class to represent a course
public:
    string courseNumber;              // Course number
    string name;                     // Course name
    vector<string> prerequisites;   // Prerequisites for the course

    Course() {}  // Default constructor

    Course(string num, string n, vector<string> prereqs) :  
        courseNumber(num), name(n), prerequisites(prereqs) {}   // Constructor to initialize the course
};

map<string, Course> loadCoursesFromFile(const string& filePath) {    // Function to load courses from a file
    map<string, Course> courses;                                    // Map to store courses
    ifstream file(filePath);                                       // File stream to read the file
    string line;                                                  // String to store each line of the file

    if (!file.is_open()) {  // if the file cannot be opened
        cout << "Error opening file or file does not exist\n";  // Print error message
        return courses; 
    }

    while (getline(file, line)) {   // Read each line of the file
        stringstream ss(line);   // Create a string stream from the line
        string token;   
        vector<string> tokens;

        while (getline(ss, token, ',')) {   // Read each token separated by a comma
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            vector<string> prereqs(tokens.begin() + 2, tokens.end());
            courses[tokens[0]] = Course(tokens[0], tokens[1], prereqs);
            // Debug output to check what's being loaded
            cout << "Loaded " << tokens[0] << " with prerequisites: ";
            for (const string& pre : prereqs) cout << pre << " ";
            cout << endl;
        } else {
            cout << "Error in file format for line: " << line << "\n";
        }
    }

    file.close();
    return courses;
}

void printCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.name << "\nPrerequisites: ";
        for (const string& pre : it->second.prerequisites) {
            cout << pre << " ";
        }
        cout << "\n";
    } else {
        cout << "Course not found\n";
    }
}

int main() {
    map<string, Course> courses;
    string filePath;
    int choice;

    cout << "Welcome to the course planner.\n";
    while (true) {
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filePath;
            courses = loadCoursesFromFile(filePath);
            break;
        case 2:
            for (const auto& pair : courses) {
                cout << pair.first << ", " << pair.second.name << "\n";
            }
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> filePath;  // Reusing filePath to read course number
            printCourse(courses, filePath);
            break;
        case 9:
            cout << "Thank you for using the course planner!\n";
            return 0;
        default:
            cout << "Invalid option.\n";
            break;
        }
    }

    return 0;
}
