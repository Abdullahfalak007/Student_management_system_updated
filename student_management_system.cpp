#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;


string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}



void writeToFile(const string& filename, const string& data) {
    ofstream file(filename.c_str(), ios::out);
    if (file.is_open()) {
        file << data;
        file.close();
        cout << "Data written to file '" << filename << "' successfully." << endl;
    } else {
        cout << "Unable to open the file '" << filename << "'." << endl;
    }
}


void readFromFile(const string& filename) {
    ifstream file(filename.c_str(), ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open the file '" << filename << "'." << endl;
    }
}

void writeStudentDataToFile(const string& filename, const string& data) {
    ofstream file(filename.c_str(), ios::app); 
    if (file.is_open()) {
        file << data << endl;
        file.close();
        cout << "Student data written to file '" << filename << "' successfully." << endl;
    } else {
        cout << "Unable to open the file '" << filename << "'." << endl;
    }
}

void writeFacultyDataToFile(const string& filename, const string& data) {
    ofstream file(filename.c_str(), ios::app); // Open the file in append mode
    if (file.is_open()) {
        file << data << endl;
        file.close();
        cout << "Faculty data written to file '" << filename << "' successfully." << endl;
    } else {
        cout << "Unable to open the file '" << filename << "'." << endl;
    }
}

struct StudentData {
    string name;
    string registrationNumber;
};

class User {
protected:
    string username;
    string password;
    bool isAdmin;

public:
    User(const string& username, const string& password, bool isAdmin = false)
        : username(username), password(password), isAdmin(isAdmin) {}

    bool authenticate(const string& enteredUsername, const string& enteredPassword) const {
        return (username == enteredUsername && password == enteredPassword);
    }

    bool isAdministrator() const {
        return isAdmin;
    }
};

class Student : public User {
private:
    string name;
    string registrationNumber;

public:
    Student(const string& name, const string& registrationNumber, const string& username, const string& password)
        : User(username, password), name(name), registrationNumber(registrationNumber) {}

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Registration Number: " << registrationNumber << endl;
    }

    const string& getName() const {
        return name;
    }

    const string& getRegistrationNumber() const {
        return registrationNumber;
    }
    
    void viewCourses() {
	    cout << "Viewing courses for student with registration number: ";
		cin >> registrationNumber;
		cout << endl;
	    cin.ignore();
	    ifstream file("courses.txt");
	    if (file.is_open()) {
	        string line;
	        while (getline(file, line)) {
	            
	            size_t pos = line.find("Course Title: ");
	            if (pos != string::npos) {
	                string courseTitle = line.substr(pos + 14);
	                cout << courseTitle << endl;
	            }
	        }
	        file.close();
	    } else {
	        cout << "Unable to open the courses file." << endl;
	    }
	}
	void viewAttendance() {
	    cout << "Viewing attendance for student with registration number: ";
	    cin >> registrationNumber;
	    cin.ignore();
	    cout << endl;
	
	    ifstream file("attendance.txt");
	    if (file.is_open()) {
	        string line;
	        bool foundStudent = false;
	        while (getline(file, line)) {
	            // Check if the line contains the student's registration number
	            size_t pos = line.find("Registration Number: ");
	            if (pos != string::npos && line.substr(pos + 21) == registrationNumber) {
	                foundStudent = true;
	                break;
	            }
	        }
	
	        if (foundStudent) {
	            // Display the attendance details, including the date
	            cout << "Attendance details:" << endl;
	            while (getline(file, line)) {
	                // Check if the line contains the date
	                size_t pos = line.find("Date: ");
	                if (pos != string::npos) {
	                    string date = line.substr(pos + 6);
	                    getline(file, line); // Read the next line
	                    pos = line.find("Attendance: ");
	                    if (pos != string::npos) {
	                        string attendance = line.substr(pos + 12);
	                        cout << "Date: " << date << endl;
	                        cout << "Attendance: " << attendance << endl;
	                    }
	                }
	            }
	        } else {
	            cout << "No attendance record found for the student." << endl;
	        }
	
	        file.close();
	    } else {
	        cout << "Unable to open the attendance file." << endl;
	    }
	}
	void viewMarksAndGrades() {
	    string registrationNumber;
	
	    cout << "Enter your registration number: ";
	    getline(cin, registrationNumber);
	
	    ifstream file("grades.txt");
	    if (file.is_open()) {
	        string line;
	        bool foundStudent = false;
	        while (getline(file, line)) {
	            // Check if the line contains the student's registration number
	            size_t pos = line.find("Registration Number: ");
	            if (pos != string::npos && line.substr(pos + 21) == registrationNumber) {
	                foundStudent = true;
	                break;
	            }
	        }
	
	        if (foundStudent) {
	            // Display the marks and grade details for the student
	            cout << "Marks and grade details:" << endl;
	            while (getline(file, line)) {
	                // Check if the line contains the assessment data for the student
	                size_t pos = line.find("Assessment Number: ");
	                if (pos != string::npos) {
	                    string assessmentNumber = line.substr(pos + 19);
	                    getline(file, line); // Read the next line
	                    pos = line.find("Assessment Type: ");
	                    if (pos != string::npos) {
	                        string assessmentType = line.substr(pos + 17);
	                        getline(file, line); // Read the next line
	                        pos = line.find("Assessment Title: ");
	                        if (pos != string::npos) {
	                            string assessmentTitle = line.substr(pos + 18);
	                            getline(file, line); // Read the next line
	                            pos = line.find("Marks: ");
	                            if (pos != string::npos) {
	                                string marks = line.substr(pos + 7);
	                                cout << "Assessment Number: " << assessmentNumber << endl;
	                                cout << "Assessment Type: " << assessmentType << endl;
	                                cout << "Assessment Title: " << assessmentTitle << endl;
	                                cout << "Marks: " << marks << endl;
	                            }
	                        }
	                    }
	                }
	
	                // Check if the line contains the grade data for the student
	                pos = line.find("Grade: ");
	                if (pos != string::npos) {
	                    string grade = line.substr(pos + 7);
	                    cout << "Grade: " << grade << endl;
	                }
	            }
	        } else {
	            cout << "No grade record found for the student." << endl;
	        }
	
	        file.close();
	    } else {
	        cout << "Unable to open the grades file." << endl;
	    }
	}
	void viewFee() {
	    cout << "Viewing fee details for student with registration number: ";
		cin >> registrationNumber;
		cout << endl;
	
	    ifstream file("fees.txt");
	    if (file.is_open()) {
	        string line;
	        bool foundStudent = false;
	        while (getline(file, line)) {
	            
	            size_t pos = line.find("Registration Number: ");
	            if (pos != string::npos && line.substr(pos + 21) == registrationNumber) {
	                foundStudent = true;
	                break;
	            }
	        }
	
	        if (foundStudent) {
	           
	            cout << "Fee details:" << endl;
	            while (getline(file, line)) {
	                
	                size_t pos = line.find("Fee: ");
	                if (pos != string::npos) {
	                    string fee = line.substr(pos + 5);
	                    cout << fee << endl;
	                }
	            }
	        } else {
	            cout << "No fee record found for the student." << endl;
	        }
	
	        file.close();
	    } else {
	        cout << "Unable to open the fees file." << endl;
	    }
	}
};

class Faculty : public User {
private:
    string name;

public:
    Faculty(const string& name, const string& username, const string& password)
        : User(username, password), name(name) {}

    void displayInfo() const {
        cout << "Name: " << name << endl;
    }
    
    void markAttendance() {
	    // Ask for the date
	    string date;
	    cout << "Enter date (DD/MM/YYYY): ";
	    cin.ignore();
	    getline(cin, date);
	
	    // Open the students.txt file to retrieve the list of students
	    ifstream studentsFile("students.txt");
	    if (!studentsFile.is_open()) {
	        cout << "Unable to open the students file." << endl;
	        return;
	    }
	
	    // Display the list of students with their registration numbers
	    cout << "List of Students:" << endl;
	    string line;
	    while (getline(studentsFile, line)) {
	        // Check if the line contains the student's registration number
	        size_t pos = line.find("Registration Number: ");
	        if (pos != string::npos) {
	            string registrationNumber = line.substr(pos + 21);
	            cout << "Registration Number: " << registrationNumber << endl;
	
	            // Display the student's name
	            getline(studentsFile, line); // Read the next line
	            pos = line.find("Name: ");
	            if (pos != string::npos) {
	                string name = line.substr(pos + 6);
	                cout << "Name: " << name << endl;
	            }
	
	            // Prompt the faculty member to mark the attendance
	            char attendance;
	            cout << "Enter attendance (P for Present, A for Absent) for the student with registration number " << registrationNumber << ": ";
	            cin >> attendance;
	
	            // Save the attendance in the attendance.txt file
	            ofstream attendanceFile("attendance.txt", ios::app);
	            if (attendanceFile.is_open()) {
	                attendanceFile << "Date: " << date << endl;
	                attendanceFile << "Registration Number: " << registrationNumber << endl;
	                attendanceFile << "Attendance: " << attendance << endl;
	                attendanceFile << endl; // Add an empty line after each attendance record
	                attendanceFile.close();
	            } else {
	                cout << "Unable to open the attendance file." << endl;
	                return;
	            }
	        }
	    }
	
	    studentsFile.close();
	    cout << "Attendance marked successfully." << endl;
	}
	
	void submitFee() {
    string registrationNumber, fee;

    cout << "Enter registration number: ";
    cin >> registrationNumber;
    cin.ignore();
    cout << "Enter fee: ";
    getline(cin, fee);
    cin.ignore();
    
    string feeDetails = "Registration Number: " + registrationNumber + "\n";
    feeDetails += "Fee: " + fee + "\n";

    ofstream file("fees.txt", ios::app);
    if (file.is_open()) {
        file << feeDetails << endl;
        cout << "Fee submitted successfully." << endl;
        file.close();
    } else {
        cout << "Unable to open the fees file." << endl;
    }
}
    
	
    void createAssessment() {
        string assessmentTitle;
        string assessmentDescription;

        cout << "Enter assessment title: ";
        cin.ignore(); 
        getline(cin, assessmentTitle);

        cout << "Enter assessment description: ";
        getline(cin, assessmentDescription);

        string assessmentData = "Title: " + assessmentTitle + "\nDescription: " + assessmentDescription;

        
        writeFacultyDataToFile("assessments.txt", assessmentData);
    }
	
	void gradeAssessment() {
    string registrationNumber;
    int totalMarks, obtainedMarks;
    string grade;

    cout << "Enter student registration number: ";
    getline(cin, registrationNumber);

    cout << "Enter total marks: ";
    cin >> totalMarks;

    cout << "Enter obtained marks: ";
    cin >> obtainedMarks;
    cin.ignore(); // Ignore the newline character

    // Calculate the percentage
    double percentage = (static_cast<double>(obtainedMarks) / totalMarks) * 100;

    // Assign the grade based on the percentage
    if (percentage >= 91) {
        grade = "A+";
    } else if (percentage >= 81) {
        grade = "A";
    } else if (percentage >= 71) {
        grade = "B";
    } else if (percentage >= 61) {
        grade = "C";
    } else if (percentage >= 51) {
        grade = "D";
    } else if (percentage >= 41) {
        grade = "E+";
    } else if (percentage >= 33) {
        grade = "E";
    } else {
        grade = "F";
    }

    // Create a string with the grade details
    string gradeDetails = "Registration Number: " + registrationNumber + "\n";
    gradeDetails += "Grade: " + grade + "\n";

    ofstream file("grades.txt", ios::app);
    if (file.is_open()) {
        file << gradeDetails << endl;
        cout << "Assessment graded successfully." << endl;
        file.close();
    } else {
        cout << "Unable to open the grades file." << endl;
    }
}
	
    void viewAttendance() {
        
        readFromFile("attendance.txt");
    }

    void viewAssessments() {
        
        readFromFile("assessments.txt");
    }

    const string& getName() const {
        return name;
    }
};


class Admin : public User {
public:
    Admin(const string& username, const string& password)
        : User(username, password, true) {}

    void registerStudent() {
        string name;
        string registrationNumber;
        string username;
        string password;

        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter student registration number: ";
        cin >> registrationNumber;

        cout << "Enter student username: ";
        cin >> username;

        cout << "Enter student password: ";
        cin >> password;

        Student student(name, registrationNumber, username, password);

        string studentData = "Name: " + name + "\nRegistration Number: " + registrationNumber + "\nUsername: " + username + "\nPassword: " + password;

        writeStudentDataToFile("students.txt", studentData);
    }

    void registerFaculty() {
        string name;
        string username;
        string password;

        cout << "Enter faculty name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter faculty username: ";
        cin >> username;

        cout << "Enter faculty password: ";
        cin >> password;

        Faculty faculty(name, username, password);

        string facultyData = "Name: " + name + "\nUsername: " + username + "\nPassword: " + password;

        writeFacultyDataToFile("faculty.txt", facultyData);
    }

    void enrollStudentInCourse() {
        string registrationNumber;
        string courseTitle;

        cout << "Enter student registration number: ";
        cin >> registrationNumber;

        cout << "Enter course title: ";
        cin.ignore();
        getline(cin, courseTitle);

        string enrollmentData = "Student Registration Number: " + registrationNumber + "\nCourse Title: " + courseTitle;

        writeStudentDataToFile("enrollments.txt", enrollmentData);
    }

    void assignCourse() {
        string facultyName, courseTitle, semester;
        int creditHours;
        cin.ignore();

        cout << "Enter faculty name: ";
        getline(cin, facultyName);

        cout << "Enter course title: ";
        getline(cin, courseTitle);

        cout << "Enter semester: ";
        getline(cin, semester);

        cout << "Enter credit hours: ";
        cin >> creditHours;
        cin.ignore();

        string courseDetails = "Faculty Name: " + facultyName + "\n";
        courseDetails += "Course Title: " + courseTitle + "\n";
        courseDetails += "Semester: " + semester + "\n";
        courseDetails += "Credit Hours: " + intToString(creditHours) + "\n";

        ofstream file("courses.txt", ios::app);
        if (file.is_open()) {
            file << courseDetails << endl;
            cout << "Course added successfully." << endl;
            file.close();
        } else {
            cout << "Unable to open the courses file." << endl;
        }
    }
};

int main() {
	main:
    string enteredUsername;
    string enteredPassword;

   
    cout << "Please log in by providing your username and password!" << endl;

    cout << "Enter username: ";
    cin >> enteredUsername;

    cout << "Enter password: ";
    cin >> enteredPassword;
    
    bool isAuthenticated = false;
    bool isAdmin = false;
    bool isFaculty = false;
    bool isStudent = false;

    Admin admin("admin_username", "admin_password"); 
    Student student("student_name", "student_registration_number", "student_username", "student_password"); 
    Faculty faculty("faculty_name", "faculty_username", "faculty_password"); 

    if (admin.authenticate(enteredUsername, enteredPassword)) {
        isAuthenticated = true;
        isAdmin = true;
        cout << "Authentication successful. You are logged in as an admin." << endl;
    } else if (student.authenticate(enteredUsername, enteredPassword)) {
        isAuthenticated = true;
        isStudent = true;
        cout << "Authentication successful. You are logged in as a student." << endl;
    } else if (faculty.authenticate(enteredUsername, enteredPassword)) {
        isAuthenticated = true;
        isFaculty = true;
        cout << "Authentication successful. You are logged in as a faculty member." << endl;
    } else {
        cout << "Authentication failed. Exiting..." << endl;
        return 0;
    }

    if (isAuthenticated) {
        while (true) {
            if (isAdmin) {
                int choice;
                cout << "Choose from the menu below:" << endl;
                cout << "Press 1 to register a student." << endl;
                cout << "Press 2 to register a faculty member." << endl;
                cout << "Press 3 to assign a course to a faculty member." << endl;
                cout << "Press 4 to enroll a student in a course." << endl;
                cout << "Press 0 to exit." << endl; 
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();
                if (choice == 0) {
                    cout << "Exiting..." << endl;
                    break; 
                }
            
                
                switch (choice) {
                    case 1:
                        admin.registerStudent();
                        break;
                    case 2:
                        admin.registerFaculty();
                        break;
                    case 3:
                        admin.assignCourse();
                        break;
                    case 4:
                        admin.enrollStudentInCourse(); 
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                }
            } else if (isFaculty) {
                int choice;
                cout << "Choose from the menu below:" << endl;
                cout << "Press 1 to mark attendance." << endl;
                cout << "Press 2 to view attendance." << endl;
                cout << "Press 3 to create an assessment." << endl;
                cout << "Press 4 to view an assessment." << endl;
                cout << "Press 5 to view mark an assesment." << endl;
                cout << "Press 6 to view cal fee." << endl;
                cout << "Press 0 to exit." << endl; 
                cout << "Enter your choice: ";
                cin >> choice;
            
                if (choice == 0) {
                    cout << "Exiting..." << endl;
                    break; 
                }
            
                
                switch (choice) {
                    case 1: {
                        faculty.markAttendance();
                        break;
                    }
                    case 2: {
                        faculty.viewAttendance();
                        break;
                    }
                    case 3: {
                        faculty.createAssessment();
                        break;
                    }
                    case 4: {
                        faculty.viewAssessments();
                        break;
                    }
                    case 5: {
                        faculty.gradeAssessment();
                        break;
                    }
                    case 6: {
                        faculty.submitFee();
                        break;
                    }
                    default:
                        cout << "Invalid choice." << endl;
                }
            } else if (isStudent) {
                int choice;
                cout << "Choose from the menu below:" << endl;
                cout << "Press 1 to view course schedule." << endl;
                cout << "Press 2 to view attendance." << endl;
                cout << "Press 3 to view grades." << endl;
                cout << "Press 4 to view fee challan." << endl;
                cout << "Press 0 to exit." << endl; 
                cout << "Enter your choice: ";
                cin >> choice;
            
                if (choice == 0) {
                    cout << "Exiting..." << endl;
                    break; 
                }
            
               
                switch (choice) {
		            case 1:
		                
		                student.viewCourses();
		                break;
		            case 2:
		                
		                student.viewAttendance();
		                break;
		            case 3:
		                
		                student.viewMarksAndGrades();
		                break;
		            case 4:
		              
		                student.viewFee();
		                break;
		            default:
		                cout << "Invalid choice." << endl;
		        }
            }
        }
    }

    return 0;
}
