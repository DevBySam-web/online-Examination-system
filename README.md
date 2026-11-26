# online Examination system

A console-based C++ project that lets an admin manage a question bank, lets students take an MCQ exam, and automatically evaluates answers and generates scorecards.

See [PROBLEM_STATEMENT.md](PROBLEM_STATEMENT.md) for the full problem definition.

## Modules
1. **Add and manage questions** - add, view, edit, delete MCQs (admin password protected).
2. **Conduct exams and record answers** - student enters details and answers all questions.
3. **Evaluate answers and calculate marks** - correct/wrong/skipped, marks, percentage, grade.
4. **Display results and generate scorecards** - scorecard, all-results table, search by roll number.

## Features
- Password-protected admin panel (default password: `admin123`)
- Persistent storage using text files
- Input validation for all menu and answer entries
- Automatic grading (A+ to F) and PASS/FAIL status
- Results history with search by roll number

## Concepts Used
Structures, functions, vectors, file handling (`ifstream` / `ofstream`), string handling, input validation, `<ctime>`.

## Requirements
- A C++11 (or newer) compiler, e.g. g++

## Build and Run
```bash
g++ -std=c++11 -o exam main.cpp
./exam          # Linux / macOS
exam.exe        # Windows
```

## How to Use
1. Choose **1. Admin** and enter the password `admin123` to add questions.
2. Choose **2. Take exam**, enter name and roll number, and answer each question (`0` skips).
3. The scorecard is shown and saved automatically.
4. Use **3** to see all results or **4** to search a scorecard by roll number.

## Sample Output
```
+--------------------------------------------+
|              SCORECARD                     |
+--------------------------------------------+
 Name        : Amit
 Roll No     : 101
 Date        : 26-11-2026
 Correct     : 1
 Wrong       : 0
 Skipped     : 1
 Marks       : 5 / 10
 Percentage  : 50.00%
 Grade       : D
 Status      : PASS
+--------------------------------------------+
```

## File Structure
```
OnlineExamSystem/
├── main.cpp              # Complete source code
├── PROBLEM_STATEMENT.md  # Problem definition
├── README.md             # This file
├── questions.txt         # Created automatically (question bank)
└── results.txt           # Created automatically (student results)
```

## Data File Format
- `questions.txt`: `id|question|opt1|opt2|opt3|opt4|correctOption|marks`
- `results.txt`: `roll|name|date|total|obtained|correct|wrong|skipped|percent|grade`

## Future Improvements
- Timer for the exam and random question order
- Negative marking and multiple-answer questions
- Student login and GUI / web version
- Export results to CSV

## Author
Your Name - Roll No - College Name
