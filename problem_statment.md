# Problem Statement: Online Examination System

## Background
Conducting exams on paper is slow: question papers must be prepared and printed, answer sheets checked by hand, and results compiled manually. This causes delays, calculation mistakes, and extra work for teachers.

## Problem
Design and implement a **console-based Online Examination System in C++** that lets an administrator build a question bank, lets students attend a multiple-choice exam, and automatically evaluates answers and produces scorecards.

## Objectives
1. Maintain a persistent question bank that can be changed at any time.
2. Conduct an MCQ exam and record each student's answers.
3. Evaluate answers automatically and compute marks without manual effort.
4. Display results and generate a scorecard for every student.

## Modules
| Module | Description |
|---|---|
| 1. Add and manage questions | Admin (password protected) can add, view, edit and delete MCQs with 4 options, correct answer and marks. |
| 2. Conduct exams and record answers | Student enters name and roll number, answers each question (or skips), and answers are recorded. |
| 3. Evaluate answers and calculate marks | Compares answers with the key, counts correct/wrong/skipped, computes total marks, percentage and grade. |
| 4. Display results and generate scorecards | Prints a formatted scorecard, saves results to file, lists all results and searches by roll number. |

## Input
- Admin: question text, four options, correct option, marks.
- Student: name, roll number, chosen option (1-4, or 0 to skip) for each question.

## Output
- Scorecard with correct/wrong/skipped counts, marks, percentage, grade and PASS/FAIL.
- Result table of all students.

## Constraints and Assumptions
- Only single-correct multiple-choice questions.
- No negative marking; unanswered questions score 0.
- Pass mark is 40%.
- Data is stored in text files (`questions.txt`, `results.txt`).
- Single-user console application.

## Grading Scale
| Percentage | Grade |
|---|---|
| 90 and above | A+ |
| 80 - 89 | A |
| 70 - 79 | B |
| 60 - 69 | C |
| 50 - 59 | D |
| below 50 | F |

## Sample Scenario
Admin adds 2 questions (5 marks each). Student "Amit" (roll 101) answers one correctly and skips the other. Result: 5/10, 50%, Grade D, PASS.
