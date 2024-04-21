// #include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

namespace fs = std::filesystem; // Namespace alias for easier usage

class Course {
public:
    std::string courseNumber;
    std::string name;
    std::vector<std::string> prerequisites;

    Course() {} // Default constructor

    Course(std::string num, std::string n, std::vector<std::string> prereqs) :
        courseNumber(num), name(n), prerequisites(prereqs) {}
};

std::map<std::string, Course> loadCoursesFromFile(const std::string& filePath) {
    std::map<std::string, Course> courses;
    if (!fs::exists(filePath)) { // Check if file exists using std::filesystem
        std::cout << "File does not exist\n";
        return courses;
    }

    std::ifstream file(fs::path(filePath).lexically_normal());
    std::string line;

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return courses;
    }

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            std::vector<std::string> prereqs(tokens.begin() + 2, tokens.end());
            courses[tokens[0]] = Course(tokens[0], tokens[1], prereqs);
        }
        else {
            std::cout << "Error in file format for line: " << line << "\n";
        }
    }

    file.close();
    return courses;
}

void printCourseList(const std::map<std::string, Course>& courses) {
    for (const auto& pair : courses) {
        std::cout << pair.first << ", " << pair.second.name << "\n";
    }
}

void printCourse(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        std::cout << it->second.courseNumber << ", " << it->second.name << "\nPrerequisites: ";
        for (const std::string& pre : it->second.prerequisites) {
            std::cout << pre << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Course not found\n";
    }
}

int main() {
    std::map<std::string, Course> courses;
    std::string filePath;
    int choice;

    std::cout << "Welcome to the course planner.\n";
    while (true) {
        std::cout << "1. Load Data Structure\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course\n";
        std::cout << "9. Exit\n";
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter filename: ";
            std::cin >> filePath;
            courses = loadCoursesFromFile(filePath);
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> filePath;  // Reusing filePath to read course number
            printCourse(courses, filePath);
            break;
        case 9:
            std::cout << "Thank you for using the course planner!\n";
            return 0;
        default:
            std::cout << "Invalid option.\n";
            break;
        }
    }

    return 0;
}