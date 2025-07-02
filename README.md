
📚 Student Grade Management System

A C++ desktop application built using wxWidgets and Visual Studio 2022, designed to help manage student grades, calculate final marks, and track performance statistics efficiently.

✨ Features

- Add, update, and delete student records
- Automatically calculate final mark and grade
- View highest, lowest, and average marks
- Save and load student data from a file
- Export student data to CSV
- Search students by ID
- View number of students per grade
- User-friendly GUI built with wxWidgets
- Confirmation dialogs for delete actions

🖥️ GUI Overview

- Textboxes for student input (ID, Name, Coursework, Final Exam)
- Buttons for common actions (Add, Update, Delete, Save CSV, Search)
- Stat Labels showing average, top, and bottom performers
- List View of all student records
- Menu Bar for file operations and help

🔧 Technologies Used

- C++
- wxWidgets (GUI framework)
- Visual Studio Community 2022
- Standard Library (fstream, map, vector)

📁 File Structure

StudentGradeManager/
├── MainFrame.h / MainFrame.cpp      # GUI and main window logic
├── Student.h / Student.cpp          # Student class and grade logic
├── App.cpp                          # wxWidgets App entry point
├── students.txt                     # Save file for student data
├── students.csv                     # CSV export
├── README.txt                       # This file

🚀 Getting Started

✅ Prerequisites

- Visual Studio 2022
- wxWidgets 3.x (configured properly in VS)
- C++17 or later

🛠️ Build Instructions

1. Clone the repository:
   git clone https://github.com/your-username/student-grade-manager.git

2. Open the .sln file in Visual Studio

3. Ensure wxWidgets is correctly linked (include/lib paths and .lib files)

4. Build and run!

⚠️ Known Issues

- Ensure wxbase32u.lib and other wx libraries are available and linked properly

📌 Future Improvements

- Add sorting by name or grade
- Implement data visualization (charts)
- Add unit tests
- Dark mode UI option

📄 License

MIT License

Developed with ❤️ using wxWidgets & C++
