// Online Examination System - C++ College Project
// Module 1: Add and manage questions
// Module 2: Conduct exams and record answers
// Module 3: Evaluate answers and calculate marks
// Module 4: Display results and generate scorecards

#include<iostream>
using namespace std;

const string QUESTION_FILE = "questions.txt";
const string RESULT_FILE   = "results.txt";
const string ADMIN_PASS    = "admin123";

struct Question {
    int id;
    string text;
    string opt[4];
    int correct;   // 1-4
    int marks;
};

struct Result {
    string roll, name, date, grade;
    int totalMarks, obtained, correct, wrong, skipped;
    double percent;
};

// ---------------- Input helpers ----------------
int readInt(const string &prompt, int lo, int hi) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= lo && x <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}

string readLine(const string &prompt) {
    string s;
    do {
        cout << prompt;
        getline(cin, s);
    } while (s.empty());
    for (char &c : s) if (c == '|') c = '/';   // '|' is our file delimiter
    return s;
}

vector<string> split(const string &s, char d) {
    vector<string> parts;
    string item;
    stringstream ss(s);
    while (getline(ss, item, d)) parts.push_back(item);
    return parts;
}

// ---------------- MODULE 1: Question management ----------------
vector<Question> loadQuestions() {
    vector<Question> qs;
    ifstream in(QUESTION_FILE);
    string line;
    while (getline(in, line)) {
        vector<string> p = split(line, '|');
        if (p.size() != 8) continue;
        Question q;
        q.id = stoi(p[0]);
        q.text = p[1];
        for (int i = 0; i < 4; i++) q.opt[i] = p[2 + i];
        q.correct = stoi(p[6]);
        q.marks = stoi(p[7]);
        qs.push_back(q);
    }
    return qs;
}

void saveQuestions(const vector<Question> &qs) {
    ofstream out(QUESTION_FILE);
    for (const Question &q : qs) {
        out << q.id << '|' << q.text << '|';
        for (int i = 0; i < 4; i++) out << q.opt[i] << '|';
        out << q.correct << '|' << q.marks << '\n';
    }
}

Question inputQuestion(int id) {
    Question q;
    q.id = id;
    q.text = readLine("  Question text : ");
    for (int i = 0; i < 4; i++)
        q.opt[i] = readLine("  Option " + to_string(i + 1) + "      : ");
    q.correct = readInt("  Correct option (1-4): ", 1, 4);
    q.marks = readInt("  Marks (1-10)        : ", 1, 10);
    return q;
}

void addQuestion(vector<Question> &qs) {
    int nextId = 1;
    for (const Question &q : qs) if (q.id >= nextId) nextId = q.id + 1;
    qs.push_back(inputQuestion(nextId));
    saveQuestions(qs);
    cout << "  Question added (ID " << nextId << ").\n";
}

void viewQuestions(const vector<Question> &qs) {
    if (qs.empty()) { cout << "  No questions available.\n"; return; }
    for (const Question &q : qs) {
        cout << "\n[ID " << q.id << "] " << q.text << "  (" << q.marks << " marks)\n";
        for (int i = 0; i < 4; i++)
            cout << "   " << i + 1 << ") " << q.opt[i] << (q.correct == i + 1 ? "   <-- correct" : "") << "\n";
    }
}

int findIndex(const vector<Question> &qs, int id) {
    for (size_t i = 0; i < qs.size(); i++) if (qs[i].id == id) return (int)i;
    return -1;
}

void editQuestion(vector<Question> &qs) {
    int id = readInt("  Enter question ID to edit: ", 1, 100000);
    int idx = findIndex(qs, id);
    if (idx < 0) { cout << "  Question not found.\n"; return; }
    qs[idx] = inputQuestion(id);
    saveQuestions(qs);
    cout << "  Question updated.\n";
}

void deleteQuestion(vector<Question> &qs) {
    int id = readInt("  Enter question ID to delete: ", 1, 100000);
    int idx = findIndex(qs, id);
    if (idx < 0) { cout << "  Question not found.\n"; return; }
    qs.erase(qs.begin() + idx);
    saveQuestions(qs);
    cout << "  Question deleted.\n";
}

void adminMenu(vector<Question> &qs) {
    string pass;
    cout << "Enter admin password: ";
    getline(cin, pass);
    if (pass != ADMIN_PASS) { cout << "  Wrong password.\n"; return; }
    int ch;
    do {
        cout << "\n--- ADMIN: Manage Questions ---\n"
             << "1. Add question\n2. View all questions\n3. Edit question\n"
             << "4. Delete question\n5. Back\n";
        ch = readInt("Choice: ", 1, 5);
        switch (ch) {
            case 1: addQuestion(qs); break;
            case 2: viewQuestions(qs); break;
            case 3: editQuestion(qs); break;
            case 4: deleteQuestion(qs); break;
        }
    } while (ch != 5);
}

// ---------------- MODULE 2: Conduct exam ----------------
vector<int> conductExam(const vector<Question> &qs) {
    vector<int> answers(qs.size(), 0);   // 0 = not answered
    cout << "\n=== EXAM STARTED === (enter 0 to skip a question)\n";
    for (size_t i = 0; i < qs.size(); i++) {
        cout << "\nQ" << i + 1 << ". " << qs[i].text << "  [" << qs[i].marks << " marks]\n";
        for (int j = 0; j < 4; j++) cout << "   " << j + 1 << ") " << qs[i].opt[j] << "\n";
        answers[i] = readInt("Your answer: ", 0, 4);
    }
    cout << "\n=== EXAM FINISHED ===\n";
    return answers;
}

// ---------------- MODULE 3: Evaluation ----------------
string gradeFor(double p) {
    if (p >= 90) return "A+";
    if (p >= 80) return "A";
    if (p >= 70) return "B";
    if (p >= 60) return "C";
    if (p >= 50) return "D";
    return "F";
}

Result evaluate(const vector<Question> &qs, const vector<int> &ans,
                const string &roll, const string &name) {
    Result r;
    r.roll = roll; r.name = name;
    r.totalMarks = r.obtained = r.correct = r.wrong = r.skipped = 0;
    for (size_t i = 0; i < qs.size(); i++) {
        r.totalMarks += qs[i].marks;
        if (ans[i] == 0) r.skipped++;
        else if (ans[i] == qs[i].correct) { r.correct++; r.obtained += qs[i].marks; }
        else r.wrong++;
    }
    r.percent = r.totalMarks ? (r.obtained * 100.0 / r.totalMarks) : 0;
    r.grade = gradeFor(r.percent);
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%d-%m-%Y", localtime(&now));
    r.date = buf;
    return r;
}

// ---------------- MODULE 4: Results & scorecards ----------------
void saveResult(const Result &r) {
    ofstream out(RESULT_FILE, ios::app);
    out << r.roll << '|' << r.name << '|' << r.date << '|' << r.totalMarks << '|'
        << r.obtained << '|' << r.correct << '|' << r.wrong << '|' << r.skipped << '|'
        << fixed << setprecision(2) << r.percent << '|' << r.grade << '\n';
}

vector<Result> loadResults() {
    vector<Result> rs;
    ifstream in(RESULT_FILE);
    string line;
    while (getline(in, line)) {
        vector<string> p = split(line, '|');
        if (p.size() != 10) continue;
        Result r;
        r.roll = p[0]; r.name = p[1]; r.date = p[2];
        r.totalMarks = stoi(p[3]); r.obtained = stoi(p[4]);
        r.correct = stoi(p[5]); r.wrong = stoi(p[6]); r.skipped = stoi(p[7]);
        r.percent = stod(p[8]); r.grade = p[9];
        rs.push_back(r);
    }
    return rs;
}

void printScorecard(const Result &r) {
    cout << "\n+--------------------------------------------+\n"
         << "|              SCORECARD                     |\n"
         << "+--------------------------------------------+\n"
         << " Name        : " << r.name << "\n"
         << " Roll No     : " << r.roll << "\n"
         << " Date        : " << r.date << "\n"
         << " Correct     : " << r.correct << "\n"
         << " Wrong       : " << r.wrong << "\n"
         << " Skipped     : " << r.skipped << "\n"
         << " Marks       : " << r.obtained << " / " << r.totalMarks << "\n"
         << " Percentage  : " << fixed << setprecision(2) << r.percent << "%\n"
         << " Grade       : " << r.grade << "\n"
         << " Status      : " << (r.percent >= 40 ? "PASS" : "FAIL") << "\n"
         << "+--------------------------------------------+\n";
}

void viewAllResults() {
    vector<Result> rs = loadResults();
    if (rs.empty()) { cout << "  No results recorded yet.\n"; return; }
    cout << "\n" << left << setw(10) << "Roll" << setw(20) << "Name" << setw(12) << "Date"
         << setw(10) << "Marks" << setw(9) << "%" << "Grade\n"
         << string(68, '-') << "\n";
    for (const Result &r : rs)
        cout << left << setw(10) << r.roll << setw(20) << r.name << setw(12) << r.date
             << setw(10) << (to_string(r.obtained) + "/" + to_string(r.totalMarks))
             << setw(9) << fixed << setprecision(1) << r.percent << r.grade << "\n";
}

void searchScorecard() {
    string roll = readLine("  Enter roll number: ");
    vector<Result> rs = loadResults();
    bool found = false;
    for (const Result &r : rs)
        if (r.roll == roll) { printScorecard(r); found = true; }
    if (!found) cout << "  No result found for roll " << roll << ".\n";
}

// ---------------- Main ----------------
void studentExam(const vector<Question> &qs) {
    if (qs.empty()) { cout << "  No questions in the system. Ask admin to add some.\n"; return; }
    string name = readLine("Enter your name   : ");
    string roll = readLine("Enter roll number : ");
    vector<int> answers = conductExam(qs);
    Result r = evaluate(qs, answers, roll, name);
    saveResult(r);
    printScorecard(r);
}

int main() {
    vector<Question> questions = loadQuestions();
    int ch;
    do {
        cout << "\n===== ONLINE EXAMINATION SYSTEM =====\n"
             << "1. Admin (manage questions)\n2. Take exam (student)\n"
             << "3. View all results\n4. Search scorecard by roll no\n5. Exit\n";
        ch = readInt("Choice: ", 1, 5);
        switch (ch) {
            case 1: adminMenu(questions); break;
            case 2: studentExam(questions); break;
            case 3: viewAllResults(); break;
            case 4: searchScorecard(); break;
        }
    } while (ch != 5);
    cout << "Goodbye!\n";
    return 0;
}

