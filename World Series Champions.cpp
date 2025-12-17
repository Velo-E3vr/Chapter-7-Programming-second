#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

string trim(const string& s) {
    int start = 0;
    while (start < (int)s.size() && isspace((unsigned char)s[start])) start++;
    int end = (int)s.size() - 1;
    while (end >= start && isspace((unsigned char)s[end])) end--;
    return s.substr(start, end - start + 1);
}

string toLowerStr(string s) {
    for (char& c : s) c = (char)tolower((unsigned char)c);
    return s;
}

/*********************************************************************
 * Function: loadTeams
 * Description: Loads all team names from Teams.txt into a vector.
 * Preconditions: file exists and is readable.
 * Postconditions: teams contains all non-empty lines from the file.
 *********************************************************************/
bool loadTeams(const string& filename, vector<string>& teams) {
    ifstream inFile(filename);
    if (!inFile) return false;

    teams.clear();
    string line;
    while (getline(inFile, line)) {
        line = trim(line);
        if (!line.empty()) teams.push_back(line);
    }
    return true;
}

/*********************************************************************
 * Function: isValidTeam
 * Description: Returns true if team exists in teams vector (case-insensitive).
 *********************************************************************/
bool isValidTeam(const vector<string>& teams, const string& team) {
    string key = toLowerStr(trim(team));
    for (const string& t : teams) {
        if (toLowerStr(t) == key) return true;
    }
    return false;
}

/*********************************************************************
 * Function: countWins
 * Description: Counts how many times 'team' appears in WorldSeriesWinners.txt.
 * Preconditions: winners file exists and is readable.
 * Postconditions: wins set to the number of matches found.
 *********************************************************************/
bool countWins(const string& filename, const string& team, int& wins) {
    ifstream inFile(filename);
    if (!inFile) return false;

    wins = 0;
    string key = toLowerStr(trim(team));
    string line;

    while (getline(inFile, line)) {
        if (toLowerStr(trim(line)) == key) {
            wins++;
        }
    }
    return true;
}

int main() {
    const string teamsFile = "Teams.txt";
    const string winnersFile = "WorldSeriesWinners.txt";

    vector<string> teams;
    if (!loadTeams(teamsFile, teams)) {
        cout << "Error: Could not open/read " << teamsFile << "\n";
        return 1;
    }

    while (true) {
        cout << "Enter a team name (or type QUIT to stop): ";
        string input;
        getline(cin, input);

        string cleaned = toLowerStr(trim(input));
        if (cleaned == "quit") break;

        if (!isValidTeam(teams, input)) {
            cout << "Team not found. Check spelling (must match Teams.txt).\n\n";
            continue;
        }

        int wins = 0;
        if (!countWins(winnersFile, input, wins)) {
            cout << "Error: Could not open/read " << winnersFile << "\n";
            return 1;
        }

        cout << trim(input) << " won " << wins << " World Series title(s).\n\n";
    }

    cout << "Goodbye!\n";
    return 0;
}

// NOTE: Program expects data files to be in the same directory as the executable.