#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const string PASSWORD = "12790";

bool isPositiveInteger(const string& s) {
    if (s.length() != 4) return false;
    for (size_t i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool isValidName(const string& s) {
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

bool stringToInt(const string& s, int& result) {
    stringstream ss(s);
    ss >> result;
    if (ss.fail() || !ss.eof()) return false;
    return true;
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }

    int day, month, year;
    if (!stringToInt(date.substr(0, 2), day)) return false;
    if (!stringToInt(date.substr(3, 2), month)) return false;
    if (!stringToInt(date.substr(6, 4), year)) return false;

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;

    return true;
}

class temp {
    string id, name, fname, mname, dob, search;
    fstream file;

public:
    void newStud();
    void viewStud();
    void searchStud();
    void editStud();
    void deleteStud();
} obj;

bool verifyPassword() {
    string input;
    cout << "Enter password to continue: ";
    getline(cin, input);
    return input == PASSWORD;
}

int main() {
    int choice;
    do {
        cout << "Student Management System\n-----------------------------\n";
        cout << "1- Add Student Record\n";
        cout << "2- View All Student Records\n";
        cout << "3- Search Student Record\n";
        cout << "4- Edit Student Record\n";
        cout << "5- Delete Student Record\n";
        cout << "6- Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter your choice(Any integer number from 1-6): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1':
                obj.newStud();
                break;
            case '2':
                if (verifyPassword()) obj.viewStud();
                else cout << "Incorrect password.\n";
                break;
            case '3':
                if (verifyPassword()) obj.searchStud();
                else cout << "Incorrect password.\n";
                break;
            case '4':
                if (verifyPassword()) obj.editStud();
                else cout << "Incorrect password.\n";
                break;
            case '5':
                if (verifyPassword()) obj.deleteStud();
                else cout << "Incorrect password.\n";
                break;
            case '6':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice!\n";
        }
        cout << endl;
    } while (choice != '6');

    return 0;
}

void temp::newStud() {
    cout << "\nEnter Student ID (4 digits): ";
    getline(cin, id);
    if (!isPositiveInteger(id)) {
        cout << "Error: Student ID must be exactly 4 positive digits.\n";
        return;
    }

    file.open("stuData.txt", ios::in);
    string line;
    while (getline(file, line)) {
        string storedID = line.substr(0, line.find('*'));
        if (storedID == id) {
            cout << "Error: Student with this ID already exists.\n";
            file.close();
            return;
        }
    }
    file.close();

    cout << "Enter Student's Name: ";
    getline(cin, name);
    if (!isValidName(name)) {
        cout << "Error: Name must contain only English letters and spaces.\n";
        return;
    }

    cout << "Enter Father's Name: ";
    getline(cin, fname);
    if (!isValidName(fname)) {
        cout << "Error: Father's Name must contain only English letters and spaces.\n";
        return;
    }

    cout << "Enter Mother's Name: ";
    getline(cin, mname);
    if (!isValidName(mname)) {
        cout << "Error: Mother's Name must contain only English letters and spaces.\n";
        return;
    }

    cout << "Enter Date of Birth(DD/MM/YYYY): ";
    getline(cin, dob);
    if (!isValidDate(dob)) {
        cout << "Error: Date of Birth must be in DD/MM/YYYY format and valid.\n";
        return;
    }

    file.open("stuData.txt", ios::app);
    file << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
    file.close();

    cout << "Record added successfully.\n";
}

void temp::viewStud() {
    file.open("stuData.txt", ios::in);
    if (!file) {
        cout << "File could not be opened.\n";
        return;
    }

    bool found = false;
    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, fname, '*') &&
           getline(file, mname, '*') &&
           getline(file, dob)) {
        found = true;
        cout << "\nStudent ID: " << id;
        cout << "\nStudent Name: " << name;
        cout << "\nFather's Name: " << fname;
        cout << "\nMother's Name: " << mname;
        cout << "\nDate of Birth: " << dob << "\n";
    }

    if (!found) {
        cout << "No records found.\n";
    }

    file.close();
}

void temp::searchStud() {
    cout << "\nEnter Student ID to search (4 digits): ";
    getline(cin, search);
    if (!isPositiveInteger(search)) {
        cout << "Error: Student ID must be exactly 4 positive digits.\n";
        return;
    }

    file.open("stuData.txt", ios::in);
    if (!file) {
        cout << "File could not be opened.\n";
        return;
    }

    bool found = false;
    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, fname, '*') &&
           getline(file, mname, '*') &&
           getline(file, dob)) {
        if (id == search) {
            found = true;
            cout << "\nStudent ID: " << id;
            cout << "\nStudent Name: " << name;
            cout << "\nFather's Name: " << fname;
            cout << "\nMother's Name: " << mname;
            cout << "\nDate of Birth: " << dob << "\n";
            break;
        }
    }

    if (!found) {
        cout << "No student found with ID: " << search << "\n";
    }

    file.close();
}

void temp::editStud() {
    string tempId;
    cout << "\nEnter Student ID to edit (4 digits): ";
    getline(cin, tempId);
    if (!isPositiveInteger(tempId)) {
        cout << "Error: Student ID must be exactly 4 positive digits.\n";
        return;
    }

    file.open("stuData.txt", ios::in);
    ofstream tempFile("temp.txt");

    bool found = false;
    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, fname, '*') &&
           getline(file, mname, '*') &&
           getline(file, dob)) {

        if (id == tempId) {
            found = true;
            cout << "\nEditing record for ID: " << id << "\n";

            cout << "Enter New Name: ";
            getline(cin, name);
            if (!isValidName(name)) {
                cout << "Error: Name must contain only English letters and spaces.\n";
                tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
                continue;
            }

            cout << "Enter New Father's Name: ";
            getline(cin, fname);
            if (!isValidName(fname)) {
                cout << "Error: Father's Name must contain only English letters and spaces.\n";
                tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
                continue;
            }

            cout << "Enter New Mother's Name: ";
            getline(cin, mname);
            if (!isValidName(mname)) {
                cout << "Error: Mother's Name must contain only English letters and spaces.\n";
                tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
                continue;
            }

            cout << "Enter New Date of Birth(DD/MM/YYYY): ";
            getline(cin, dob);
            if (!isValidDate(dob)) {
                cout << "Error: Date of Birth must be in DD/MM/YYYY format and valid.\n";
                tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
                continue;
            }
        }

        tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
    }

    file.close();
    tempFile.close();

    remove("stuData.txt");
    rename("temp.txt", "stuData.txt");

    if (found)
        cout << "Record updated successfully.\n";
    else
        cout << "Student ID not found.\n";
}

void temp::deleteStud() {
    string tempId;
    cout << "\nEnter Student ID to delete (4 digits): ";
    getline(cin, tempId);
    if (!isPositiveInteger(tempId)) {
        cout << "Error: Student ID must be exactly 4 positive digits.\n";
        return;
    }

    file.open("stuData.txt", ios::in);
    ofstream tempFile("temp.txt");

    bool found = false;
    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, fname, '*') &&
           getline(file, mname, '*') &&
           getline(file, dob)) {

        if (id == tempId) {
            found = true;
            cout << "Record with ID " << id << " deleted.\n";
            continue;
        }

        tempFile << id << "*" << name << "*" << fname << "*" << mname << "*" << dob << "\n";
    }

    file.close();
    tempFile.close();

    remove("stuData.txt");
    rename("temp.txt", "stuData.txt");

    if (!found)
        cout << "Student ID not found.\n";
}

