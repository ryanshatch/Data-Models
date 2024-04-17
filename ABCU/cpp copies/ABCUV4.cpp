#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course() {} // Default constructor

    Course(string num, string n, vector<string> prereqs) :
        courseNumber(num), name(n), prerequisites(prereqs) {}
};

map<string, Course> loadCoursesFromFile(const string& filePath) {
    map<string, Course> courses;
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cout << "Error opening file or file does not exist\n";
        return courses;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            vector<string> prereqs(tokens.begin() + 2, tokens.end());
            courses[tokens[0]] = Course(tokens[0], tokens[1], prereqs);
        }
        else {
            cout << "Error in file format for line: " << line << "\n";
        }
    }

    file.close();
    return courses;
}

void printCourseList(const map<string, Course>& courses) {
    for (const auto& pair : courses) {
        cout << pair.first << ", " << pair.second.name << "\n";
    }
}

void printCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.name << "\nPrerequisites: ";
        for (const string& pre : it->second.prerequisites) {
            cout << pre << " ";
        }
        cout << "\n";
    }
    else {
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
            printCourseList(courses);
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