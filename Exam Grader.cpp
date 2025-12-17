#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int NUM_Q = 20;
const double PASS_PERCENT = 70.0;

/*********************************************************************
 * Function: loadAnswers
 * Description: Loads exactly 'size' answer letters from a file into an array.
 * Parameters: filename (in), answers[] (out), size (in)
 * Returns: true if file opened and read succeeded; false otherwise.
 * Preconditions: size > 0; file exists and contains at least 'size' answers.
 * Postconditions: answers[] is filled if true is returned.
 *********************************************************************/
bool loadAnswers(const string& filename, char answers[], int size) {
    ifstream inFile(filename);
    if (!inFile) return false;

    for (int i = 0; i < size; i++) {
        if (!(inFile >> answers[i])) {   // reads the single letter on each line
            return false;
        }
    }
    return true;
}

/*********************************************************************
 * Function: gradeExam
 * Description: Compares correct vs student answers and stores missed questions.
 * Parameters: correct[] (in), student[] (in), size (in),
 *             missed[] (out), missedCount (out)
 * Returns: Number of correct answers.
 * Preconditions: correct[] and student[] filled with 'size' answers.
 * Postconditions: missed[] contains missed question numbers (1-based),
 *                 missedCount is set.
 *********************************************************************/
int gradeExam(const char correct[], const char student[], int size,
    int missed[], int& missedCount) {
    int numCorrect = 0;
    missedCount = 0;

    for (int i = 0; i < size; i++) {
        if (student[i] == correct[i]) {
            numCorrect++;
        }
        else {
            missed[missedCount] = i + 1; // store question number (1-based)
            missedCount++;
        }
    }
    return numCorrect;
}

/*********************************************************************
 * Function: calcPercent
 * Description: Calculates exam score percentage.
 *********************************************************************/
double calcPercent(int numCorrect, int total) {
    return (static_cast<double>(numCorrect) / total) * 100.0;
}

/*********************************************************************
 * Function: didPass
 * Description: Returns true if percent is at or above PASS_PERCENT.
 *********************************************************************/
bool didPass(double percent) {
    return percent >= PASS_PERCENT;
}

/*********************************************************************
 * Function: printReport
 * Description: Prints a formatted exam report.
 *********************************************************************/
void printReport(const int missed[], int missedCount,
    int numCorrect, int total, double percent, bool pass) {
    int numIncorrect = total - numCorrect;

    cout << fixed << setprecision(1);
    cout << "----- Exam Report -----\n";
    cout << "Correct:   " << numCorrect << "\n";
    cout << "Incorrect: " << numIncorrect << "\n";
    cout << "Score:     " << percent << "%\n";
    cout << "Result:    " << (pass ? "PASS" : "FAIL") << "\n\n";

    cout << "Missed Questions: ";
    if (missedCount == 0) {
        cout << "None\n";
    }
    else {
        for (int i = 0; i < missedCount; i++) {
            cout << missed[i] << (i < missedCount - 1 ? ", " : "\n");
        }
    }
}

int main() {
    char correct[NUM_Q];
    char student[NUM_Q];
    int missed[NUM_Q];
    int missedCount = 0;

    // These must match your actual filenames exactly:
    const string correctFile = "CorrectAnswers.txt";
    const string studentFile = "StudentAnswers.txt";

    if (!loadAnswers(correctFile, correct, NUM_Q)) {
        cout << "Error: Could not open/read " << correctFile << "\n";
        return 1;
    }
    if (!loadAnswers(studentFile, student, NUM_Q)) {
        cout << "Error: Could not open/read " << studentFile << "\n";
        return 1;
    }

    int numCorrect = gradeExam(correct, student, NUM_Q, missed, missedCount);
    double percent = calcPercent(numCorrect, NUM_Q);
    bool pass = didPass(percent);

    printReport(missed, missedCount, numCorrect, NUM_Q, percent, pass);
    return 0;
}

// NOTE: Program expects data files to be in the same directory as the executable.