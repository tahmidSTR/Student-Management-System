# Student Management System

## Overview

The **Student Management System** is a C++ console-based application used to store, manage, and retrieve student records. It provides features for adding, viewing, searching, editing, and deleting student information. The program includes basic data validation and password protection for sensitive operations, ensuring that only authorized users can modify or access certain records.

## Features

* **Add Student Record** – Add a new student with ID, name, parents’ names, and date of birth.
* **View All Student Records** – Display all stored records (password protected).
* **Search Student Record** – Search for a student by ID and display details (password protected).
* **Edit Student Record** – Modify an existing student’s details (password protected).
* **Delete Student Record** – Remove a student’s record from the system (password protected).
* **Exit** – Close the application.

## Technologies Used

* **Language:** C++
* **IDE:** Dev-C++ Version 5.11
* **Compiler:** TDM-GCC 4.9.2 64-bit Release

## System Requirements

* Windows operating system
* Dev-C++ 5.11 or any compatible C++ compiler

## Installation and Execution

1. Install **Dev-C++ 5.11** or any C++ compatible IDE.
2. Open the project file in the suitble development environment.
3. Ensure the compiler is set to **TDM-GCC 4.9.2 64-bit Release** or any compatible G++ compiler, preferably mingw C++ compiler .
4. Compile the program (**Execute → Compile** or press `F9`).
5. Run the program (**Execute → Run** or press `Ctrl + F10`).

## Example Output

Below is an example of searching for a student record:

```
Student Management System
-----------------------------
1- Add Student Record
2- View All Student Records
3- Search Student Record
4- Edit Student Record
5- Delete Student Record
6- Exit
-----------------------------
Enter your choice: 3
Enter password to continue: 12790

Enter Student ID to search (4 digits): 1234

Student ID: 1234
Student Name: John
Father's Name: Clive
Mother's Name: Ellie
Date of Birth: 13/06/2001
```
