#include <iostream>   // For input/output (cin, cout)
#include <fstream>    // For file handling (ifstream, ofstream, fstream)
#include <sstream>    // For string stream operations (for parsing)
#include <cctype>     // For character handling functions (toupper)
#include <string>     // For using string data type
#include <iomanip>    // For output formatting 


using namespace std;


// Define a structure to hold all student information
struct Student {
    int rollno; 
    string name;
    string gender;
    int age;
    float cgpa;
    string grade;
    string city;
  string mobile;
    float marks_subject_1;
    float marks_subject_2;
    float marks_subject_3;
    float totalmarks;
    float average;
};


const int SIZE = 100; // Maximum number of student records allowed
Student students[SIZE]; // Array to store student data
int numStudents = 0;    // Current number of students in memory


// Function prototypes
void load();
void save();
void newRecord();
void display();
void searchbyname();
void deletebyrollno();
void updatebymobile();
void sort();


int main() {
    char choice;


    cout <<
    "=====================================================" << endl <<
    "C++ SEMESTER PROJECT - ASSIGNMENT 4" << endl <<
    "Student Record Management System" << endl <<
    "=====================================================" << endl;


    /*
     => Main menu loop.
     => Prompts the user for input until they choose to exit (option I).
     => Each case calls the appropriate function for the desired task.
     */
    do {
        // Display menu options
        cout << "\nA. Add New Student Record";
        cout << "\nB. Display All Student Records";
        cout << "\nC. Save Records to File";
        cout << "\nD. Load Records from File";
        cout << "\nE. Search Student by Name";
        cout << "\nF. Delete Record by Roll No.";
        cout << "\nG. Update Record by Mobile No";
        cout << "\nH. Sort Records by Roll No";
        cout << "\nI. Exit";
        cout << "\nEnter your choice(A-I): ";
        cin >> choice;
        choice = toupper(choice); // Convert input to uppercase for flexibility


        switch (choice) {
            case 'I':
                cout << "Exiting... Thank you!\n";
                break;


            case 'A': 
                newRecord();
                break;
            
            case 'B':
                display();   
break;


            case 'C':
                save();
                break;


            case 'D':
                load();
                cout << "✅ Records loaded from file successfully.\n";
                cout << "----------------------------------------\n";
                break;


            case 'E':
                searchbyname();
                break;


            case 'F':
                deletebyrollno();
                break;


            case 'G':
                updatebymobile();
                break;


            case 'H':
                sort();
                break;


            default:
                cout << "❌ Invalid choice! Enter a letter from A to I.\n";
                break;    
        }
    } while (choice != 'I');


    return 0;
}


// Function to load student records from a file into memory
void load() {
    ifstream inFile("students.txt");


    // Try to open file; if failed, display error
    try { 
        if (!inFile.is_open()) 
            throw "Error: Could not open the file for reading.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    numStudents = 0;
    string line;


    /*
     => Read file line-by-line.
     => Each line represents a student's data, fields separated by tab characters.
     */
    while (getline(inFile, line)) {
        if (line.empty()) continue;


        stringstream ss(line);


        string temp;


        // Parse and assign each field from the file line
        getline(ss, temp, '\t'); 
        students[numStudents].rollno = stoi(temp);


        getline(ss, students[numStudents].name, '\t');
        getline(ss, students[numStudents].gender, '\t');


        getline(ss, temp, '\t'); 
        students[numStudents].age = stoi(temp);


        getline(ss, temp, '\t'); 
        students[numStudents].cgpa = stof(temp);


        getline(ss, students[numStudents].grade, '\t');
        getline(ss, students[numStudents].city, '\t');
        getline(ss, students[numStudents].mobile, '\t');


        getline(ss, temp, '\t'); 
        students[numStudents].marks_subject_1 = stof(temp);


        getline(ss, temp, '\t'); 
        students[numStudents].marks_subject_2 = stof(temp);


        getline(ss, temp, '\t'); 
        students[numStudents].marks_subject_3 = stof(temp);


        getline(ss, temp, '\t'); 
        students[numStudents].totalmarks = stof(temp);


        numStudents++;
    }


    inFile.close();
}


// Function to save all student records to a text file
void save() {
    load();
    bool found = false;
    ofstream outFile("students.txt");


    try { 
        if (!outFile.is_open()) 
            throw "Error! Could not open the file for writing.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    if (outFile.is_open()) {
        found = true;


        /*
         => Write each student's data on a new line
         => using tab characters as field separators.
         */
        for (int i = 0; i < numStudents; ++i) {
            outFile << students[i].rollno << '\t'
                    << students[i].name << '\t'
                    << students[i].gender << '\t'
                    << students[i].age << '\t'
                    << students[i].cgpa << '\t'
                    << students[i].grade << '\t'
                    << students[i].city << '\t'
                    << students[i].mobile << '\t'
                    << students[i].marks_subject_1 << '\t'
                    << students[i].marks_subject_2 << '\t'
                    << students[i].marks_subject_3 << '\t'
                    << students[i].totalmarks << '\n';
        }
    }


    outFile.close();


    if (found) {
        cout << "✅ Records saved to file successfully.\n";
    }


    cout << "--------------------------------------\n";
}


/*
 => Function to add new student records.
 => Prompts the user for the number of students, takes input for each field,
 => validates entries, calculates totals and grade, and writes the data to file.
 */
void newRecord() {
    int num;
    cout << "Enter number of students: ";
    cin >> num;


    cout << "---- Enter details of " << num << " students ----\n";


    for (int i = 0; i < num; ++i) {
        cout << "\nStudent " << i + 1 << ":\n";


        // Validate roll number
        do {
            cout << "Enter Roll No: ";
            cin >> students[i].rollno;
            try {
                if (students[i].rollno <= 0)
                    throw "❌ Negative values are not allowed.";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].rollno <= 0);


        cin.ignore(); // Clear input buffer


        // Take string inputs
        cout << "Name: ";
        getline(cin, students[i].name);


        cout << "Gender: ";
        getline(cin, students[i].gender);


        // Validate age
        do {
            cout << "Age: ";
            cin >> students[i].age;
            try {
                if (students[i].age < 0)
                    throw "❌ Negative values are not allowed.";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].age < 0);


        // Validate CGPA
        do {
            cout << "CGPA: ";
            cin >> students[i].cgpa;
            try {
                if (students[i].cgpa < 0 || students[i].cgpa > 4.0)
                    throw "❌ Invalid CGPA! Please enter a number between 0.00 and 4.00\n";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].cgpa < 0 || students[i].cgpa > 4.0);


        cin.ignore();
        cout << "City: ";
        getline(cin, students[i].city);


        // Validate mobile number
        do {
            cout << "Mobile: ";
            cin >> students[i].mobile;
            try {
                if (students[i].mobile.length() < 10 || students[i].mobile.length() > 12)
                    throw "❌ Invalid mobile number! Please enter a 10-12 digit number.\n";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].mobile.length() < 10 || students[i].mobile.length() > 12);


        // Validate subject marks
        do {
            cout << "Marks in Subject 1 (out of 100): ";
            cin >> students[i].marks_subject_1;
            try {
                if (students[i].marks_subject_1 < 0 || students[i].marks_subject_1 > 100)
                    throw "❌ Invalid input. Marks must be between 0 and 100.";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].marks_subject_1 < 0 || students[i].marks_subject_1 > 100);


        do {
            cout << "Marks in Subject 2 (out of 100): ";
            cin >> students[i].marks_subject_2;
            try {
                if (students[i].marks_subject_2 < 0 || students[i].marks_subject_2 > 100)
                    throw "❌ Invalid input. Marks must be between 0 and 100.";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].marks_subject_2 < 0 || students[i].marks_subject_2 > 100);


        do {
            cout << "Marks in Subject 3 (out of 100): ";
            cin >> students[i].marks_subject_3;
            try {
                if (students[i].marks_subject_3 < 0 || students[i].marks_subject_3 > 100)
                    throw "❌ Invalid input. Marks must be between 0 and 100.";
            } catch (const char* msg) {
                cout << msg << endl;
            }
        } while (students[i].marks_subject_3 < 0 || students[i].marks_subject_3 > 100);


        // Calculate total, average, and grade
        students[i].totalmarks = students[i].marks_subject_1 + students[i].marks_subject_2 + students[i].marks_subject_3;
        students[i].average = students[i].totalmarks / 3.0;


        if (students[i].average >= 90) students[i].grade = "A";
        else if (students[i].average >= 80) students[i].grade = "B";
        else if (students[i].average >= 70) students[i].grade = "C";
        else if (students[i].average >= 60) students[i].grade = "D";
        else if (students[i].average >= 50) students[i].grade = "E";
        else students[i].grade = "F";
    }


    // Save records immediately to file
    ofstream outFile("students.txt", ios::app);
    try {
        if (!outFile.is_open()) 
            throw "Error! Could not open the file for writing.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    if (outFile.is_open()) {
        for (int i = 0; i < num; ++i) {
            outFile << students[i].rollno << '\t'
                    << students[i].name << '\t'
                    << students[i].gender << '\t'
                    << students[i].age << '\t'
                    << students[i].cgpa << '\t'
                    << students[i].grade << '\t'
                    << students[i].city << '\t'
                    << students[i].mobile << '\t'
                    << students[i].marks_subject_1 << '\t'
                    << students[i].marks_subject_2 << '\t'
                    << students[i].marks_subject_3 << '\t'
                    << students[i].totalmarks << '\n';
        }
        outFile.close();
        cout << "\n✅ Student records have been written to students.txt\n";
    } else {
        cout << "\nError: Could not open file for writing.\n";
    }


    cout << "-------------------------------\n";
}


// Display all student records from the file
void display() {
    load(); // Load data from file into the array


    cout << "\n--- Student Records ---\n";


    for (int j = 0; j < numStudents; j++) {
        cout << "\n-------------------------" << endl;
        cout << "Student " << j + 1 << ":" << endl;
        cout << "-------------------------" << endl;


        // Print each field of the student record
        cout << left << setw(15) << "Roll No:" << students[j].rollno << endl;
        cout << left << setw(15) << "Name:" << students[j].name << endl;
        cout << left << setw(15) << "Gender:" << students[j].gender << endl;
        cout << left << setw(15) << "Age:" << students[j].age << endl;
        cout << left << setw(15) << "CGPA:" << students[j].cgpa << endl;
        cout << left << setw(15) << "Grade:" << students[j].grade << endl;
        cout << left << setw(15) << "City:" << students[j].city << endl;
        cout << left << setw(15) << "Mobile:" << students[j].mobile << endl;
        cout << left << setw(15) << "Marks 1:" << students[j].marks_subject_1 << endl;
        cout << left << setw(15) << "Marks 2:" << students[j].marks_subject_2 << endl;
        cout << left << setw(15) << "Marks 3:" << students[j].marks_subject_3 << endl;
        cout << left << setw(15) << "Total Marks:" << students[j].totalmarks << endl;
    }


    cout << "-------------------------------\n";
}


// Search and display a student record by name
void searchbyname() {
    string search;
    cout << "Enter a Name to Search: ";
    cin.ignore();
    getline(cin, search);


    load(); // Load records from file
    bool found = false;


    /*
     => Loop through all student records
     => If a name matches, display that student
     */
    for (int j = 0; j < numStudents; ++j) {
        if (students[j].name == search) {
            found = true;
            cout << "\n--- Record Found ---\n";
            // Display matching student's full info
            cout << "Roll No: " << students[j].rollno << endl;
            cout << "Name: " << students[j].name << endl;
            cout << "Gender: " << students[j].gender << endl;
            cout << "Age: " << students[j].age << endl;
            cout << "CGPA: " << students[j].cgpa << endl;
            cout << "Grade: " << students[j].grade << endl;
            cout << "City: " << students[j].city << endl;
            cout << "Mobile: " << students[j].mobile << endl;
            cout << "Marks 1: " << students[j].marks_subject_1 << endl;
            cout << "Marks 2: " << students[j].marks_subject_2 << endl;
            cout << "Marks 3: " << students[j].marks_subject_3 << endl;
            cout << "Total Marks: " << students[j].totalmarks << endl;
            
            break;
        }
    }


    if (!found){
        cout << "❌ No record found with the given name.\n";
    }
    cout << "-------------------------------\n";
}


// Delete a student record based on roll number
void deletebyrollno() {
    int deleteRollno;
    bool found = false;
    load(); // Load all records


    ofstream outFile("students.txt");
    try {
        if (!outFile.is_open())
            throw "Error! Could not open the file for writing.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    cout << "Enter Roll No. to delete: ";
    cin >> deleteRollno;


    /*
     => Re-write all student records to file
     => Except the one with matching roll number
     */
    for (int j = 0; j < numStudents; ++j) {
        if (students[j].rollno == deleteRollno) {
            found = true;
            continue; // Skip the student to be deleted
        }


        // Write all other students to file
        outFile << students[j].rollno << '\t'
                << students[j].name << '\t'
                << students[j].gender << '\t'
                << students[j].age << '\t'
                << students[j].cgpa << '\t'
                << students[j].grade << '\t'
                << students[j].city << '\t'
                << students[j].mobile << '\t'
                << students[j].marks_subject_1 << '\t'
                << students[j].marks_subject_2 << '\t'
                << students[j].marks_subject_3 << '\t'
                << students[j].totalmarks << '\n';
    }


    if (found)
        cout << "✅ Record deleted successfully.\n";
    else
        cout << "❌ Roll No not found.\n";


    cout << "-------------------------------\n";
}


// Update any student record by matching mobile number
void updatebymobile() {
    load(); // Load all data


    string mobile;
    bool found = false;


    cout << "Enter mobile number to update: ";
    cin >> mobile;
    cin.ignore();


    /*
     => Loop through the list to find the student
     => whose mobile number matches
     */
    for (int j = 0; j < numStudents; ++j) {
        if (students[j].mobile == mobile) {
            found = true;
            char choice;


            cout << "A. Roll No\nB. Name\nC. Gender\nD. Age\nE. CGPA\nF. City\nG. Mobile\nH. Marks 1\nI. Marks 2\nJ. Marks 3\n";
            cout << "Enter your choice (A to J) to update an attribute: ";
            cin >> choice;
            choice = toupper(choice);
            cin.ignore();


            // Update the selected attribute
            switch (choice) {
                case 'A': cout << "Enter New Roll No: "; cin >> students[j].rollno; break;
                case 'B': cout << "Enter New Name: "; getline(cin, students[j].name); break;
                case 'C': cout << "Enter New Gender: "; getline(cin, students[j].gender); break;
                case 'D': cout << "Enter New Age: "; cin >> students[j].age; break;
                case 'E': cout << "Enter New CGPA: "; cin >> students[j].cgpa; break;
                case 'F': cout << "Enter New City: "; getline(cin, students[j].city); break;
                case 'G': cout << "Enter New Mobile: "; getline(cin, students[j].mobile); break;
                case 'H': cout << "Enter New Marks 1: "; cin >> students[j].marks_subject_1; break;
                case 'I': cout << "Enter New Marks 2: "; cin >> students[j].marks_subject_2; break;
                case 'J': cout << "Enter New Marks 3: "; cin >> students[j].marks_subject_3; break;
                default: cout << "❌ Invalid input.\n"; return;
            }


            // Recalculate total and grade
            students[j].totalmarks = students[j].marks_subject_1 + students[j].marks_subject_2 + students[j].marks_subject_3;
            students[j].average = students[j].totalmarks / 3.0;


            if (students[j].average >= 90) students[j].grade = "A";
            else if (students[j].average >= 80) students[j].grade = "B";
            else if (students[j].average >= 70) students[j].grade = "C";
            else if (students[j].average >= 60) students[j].grade = "D";
            else if (students[j].average >= 50) students[j].grade = "E";
            else students[j].grade = "F";


            break;
        }
    }


    if (!found) {
        cout << "❌ Student not found!\n";
        cout << "-------------------------------\n";
        return;
    }


    // Write updated records back to file
    ofstream outFile("students.txt");
    try {
        if (!outFile.is_open())
            throw "Error! Could not open the file for writing.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    for (int j = 0; j < numStudents; ++j) {
        outFile << students[j].rollno << '\t'
                << students[j].name << '\t'
                << students[j].gender << '\t'
                << students[j].age << '\t'
                << students[j].cgpa << '\t'
                << students[j].grade << '\t'
                << students[j].city << '\t'
                << students[j].mobile << '\t'
                << students[j].marks_subject_1 << '\t'
                << students[j].marks_subject_2 << '\t'
                << students[j].marks_subject_3 << '\t'
                << students[j].totalmarks << '\n';
    }


    outFile.close();
    cout << "✅ Record updated successfully.\n";
    cout << "-------------------------------\n";
}


// Sort student records by roll number
void sort() {
    bool found = false;
    load(); // Load student records


    /*
     => Bubble sort algorithm:
     => Repeatedly swap adjacent elements if they are in the wrong order.
     */
    for (int j = 0; j < numStudents - 1; ++j) {
        for (int k = 0; k < numStudents - j - 1; ++k) {
            if (students[k].rollno > students[k + 1].rollno) {
                Student temp = students[k];
                students[k] = students[k + 1];
                students[k + 1] = temp;
            }
        }
    }


    // Write sorted data back to the file
    ofstream outFile("students.txt");
    try {
        if (!outFile.is_open())
            throw "Error! Could not open the file for writing.";
    } catch (const char* msg) {
        cout << msg << endl;
        return;
    }


    if (outFile.is_open()) {
        found = true;
        for (int j = 0; j < numStudents; ++j) {
            outFile << students[j].rollno << '\t'
                    << students[j].name << '\t'
                    << students[j].gender << '\t'
                    << students[j].age << '\t'
                    << students[j].cgpa << '\t'
                    << students[j].grade << '\t'
                    << students[j].city << '\t'
                    << students[j].mobile << '\t'
                    << students[j].marks_subject_1 << '\t'
                    << students[j].marks_subject_2 << '\t'
                    << students[j].marks_subject_3 << '\t'
                    << students[j].totalmarks << '\n';
        }
    }


    outFile.close();


    if (found) {
        cout << "✅ Student records sorted by Roll No.\n";
        cout << "--------------------------------------\n";
    }
}
