
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_COURSES = 1000;

// Parallel arrays for courses
string courseIds[MAX_COURSES];
string titles[MAX_COURSES];
int creditHours[MAX_COURSES];
int courseCount = 0;

//  Helper: split a CSV line into 3 parts
bool parseCourseLine(const string &line, string &id, string &title, int &credit) {
    size_t p1 = line.find(',');
    if (p1 == string::npos) return false;
    size_t p2 = line.find(',', p1 + 1);
    if (p2 == string::npos) return false;

    id = line.substr(0, p1);
    title = line.substr(p1 + 1, p2 - (p1 + 1));
    string creditStr = line.substr(p2 + 1);
    credit = atoi(creditStr.c_str()); // simple conversion

    if (id.empty() || title.empty()) return false;
    return true;
}

//Load and Save Courses
void loadCourses() {
    ifstream fin("courses.txt");
    courseCount = 0;
    if (!fin.is_open()) return;

    string line;
    while (getline(fin, line) && courseCount < MAX_COURSES) {
        string id, title;
        int credit;
        if (parseCourseLine(line, id, title, credit)) {
            courseIds[courseCount] = id;
            titles[courseCount] = title;
            creditHours[courseCount] = credit;
            courseCount++;
        }
    }
    fin.close();
}

void saveCourses() {
    ofstream fout("courses.txt");
    for (int i = 0; i < courseCount; ++i) {
        fout << courseIds[i] << "," << titles[i] << "," << creditHours[i] << "\n";
    }
    fout.close();
}

// Course Helpers
int findCourseIndex(const string &id) {
    for (int i = 0; i < courseCount; ++i) {
        if (courseIds[i] == id) return i;
    }
    return -1;
}

void listCourses() {
    if (courseCount == 0) {
        cout << "No courses available.\n";
        return;
    }
    cout << "\nAll courses:\n";
    for (int i = 0; i < courseCount; ++i) {
        cout << courseIds[i] << " | " << titles[i] << " | " << creditHours[i] << "\n";
    }
}

// CRUD OPERATIONS
void addCourse() {
    if (courseCount >= MAX_COURSES) {
        cout << "Course list is full.\n"; return;
    }
    string id, title, creditStr;
    cout << "Enter course ID (e.g. DIT101): ";
    getline(cin, id);
    if (id.empty()) { cout << "ID cannot be empty.\n"; return; }
    if (findCourseIndex(id) != -1) { cout << "Course already exists.\n"; return; }

    cout << "Enter course title: ";
    getline(cin, title);
    if (title.empty()) { cout << "Title cannot be empty.\n"; return; }

    cout << "Enter credit hours (1-6): ";
    getline(cin, creditStr);
    int credit = atoi(creditStr.c_str());
    if (credit < 1 || credit > 6) { cout << "Invalid credit (must be 1-6).\n"; return; }

    courseIds[courseCount] = id;
    titles[courseCount] = title;
    creditHours[courseCount] = credit;
    courseCount++;
    saveCourses();
    cout << "Course added.\n";
}

void deleteCourse() {
    string id;
    cout << "Enter course ID to delete: ";
    getline(cin, id);
    int idx = findCourseIndex(id);
    if (idx == -1) { cout << "Course not found.\n"; return; }
    // shift left
    for (int i = idx; i < courseCount - 1; ++i) {
        courseIds[i] = courseIds[i+1];
        titles[i] = titles[i+1];
        creditHours[i] = creditHours[i+1];
    }
    courseCount--;
    saveCourses();
    cout << "Course deleted.\n";
}

void updateCourse() {
    string id;
    cout << "Enter course ID to update: ";
    getline(cin, id);
    int idx = findCourseIndex(id);
    if (idx == -1) { cout << "Course not found.\n"; return; }

    string newTitle, creditStr;
    cout << "Current title: " << titles[idx] << "\n";
    cout << "Enter new title (leave it blank to keep the current): ";
    getline(cin, newTitle);
    if (!newTitle.empty()) titles[idx] = newTitle;

    cout << "Current credits: " << creditHours[idx] << "\n";
    cout << "Enter new credit hours (1-6) or leave empty to keep current: ";
    getline(cin, creditStr);
    if (!creditStr.empty()) {
        int newCredit = atoi(creditStr.c_str());
        if (newCredit >= 1 && newCredit <= 6) creditHours[idx] = newCredit;
        else cout << "Invalid credit entered; keeping previous value.\n";
    }
    saveCourses();
    cout << "Course updated.\n";
}

void searchCourse() {
    string q;
    cout << "Enter course ID or part of title to search: ";
    getline(cin, q);
    bool found = false;
    for (int i = 0; i < courseCount; ++i) {
        if (courseIds[i] == q || titles[i].find(q) != string::npos) {
            cout << courseIds[i] << " | " << titles[i] << " | " << creditHours[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matching course found.\n";
}

// User: Register & Login
bool login() {
    string username, password;
    cout << "Enter your Username: ";
    getline(cin, username);
    cout << "Enter your Password: ";
    getline(cin, password);

    ifstream fin("users.txt");
    if (!fin.is_open()) {
        cout << "No users registered yet. Please register first.\n";
        return false;
    }
    string line;
    while (getline(fin, line)) {
        size_t p = line.find(',');
        if (p == string::npos) continue;
        string u = line.substr(0, p);
        string pss = line.substr(p + 1);
        if (u == username && pss == password) { fin.close(); return true; }
    }
    fin.close();
    cout << "Wrong username or password.\n";
    return false;
}

void registerUser() {
    string username, password;
    cout << "Choose a username: ";
    getline(cin, username);
    if (username.empty()) { cout << "Username cannot be empty.\n"; return; }
    // check duplicate
    ifstream fin("users.txt");
    if (fin.is_open()) {
        string line;
        while (getline(fin, line)) {
            size_t p = line.find(',');
            if (p == string::npos) continue;
            string u = line.substr(0, p);
            if (u == username) { cout << "Username already exists. Choose another.\n"; fin.close(); return; }
        }
        fin.close();
    }
    cout << "Choose a password: ";
    getline(cin, password);
    ofstream fout("users.txt", ios::app); // append
    fout << username << "," << password << "\n";
    fout.close();
    cout << "Registration complete. You can now login.\n";
}

//  Menus
void courseMenu() {
    while (true) {
        cout << "\nCourse Management System Menu\n";
        cout << "1. Add Course\n2. Delete Course\n3. Search Course\n4. Update Course\n5. List All Courses\n6. Logout\n";
        cout << "Enter Option: ";
        string Option; getline(cin, Option);
        if (Option == "1") addCourse();
        else if (Option == "2") deleteCourse();
        else if (Option == "3") searchCourse();
        else if (Option == "4") updateCourse();
        else if (Option == "5") listCourses();
        else if (Option == "6") { cout << "Logged out Succefully.\n"; break; }
        else cout << "Invalid Option.\n";
    }
}

int main() {
    while (true) {
        cout << "Welcome to Course Management System\n";
        cout << "1. Login\n2. Register\n3. Exit\n";
        cout << "Enter Option: ";
        string Option; getline(cin, Option);

        if (Option == "1") {
            if (login()) {
                loadCourses();
                courseMenu();
            }
        } else if (Option == "2") {
            registerUser();
        } else if (Option == "3") {
            cout << "Thank for using Course Management System!\n";
            break;
        } else {
            cout << "Invalid Option.\n";
        }
    }
    return 0;
}
