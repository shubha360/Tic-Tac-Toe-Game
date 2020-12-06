#include<iostream>
#include<ctime>
#include<vector>

#include"TicTacToe.h"

using namespace std;

// Exception class for input invalidation
class INPUT_INVALIDATION_EXCEPTION : public exception {

    public:

    virtual const char* what() const throw() {

        return "Player's input was invalid.";
    }
};

// Preparing everything
void TicTacToe :: initialization() {

    filledCount = 0;

    for (auto& rows : mainTable) {
        for (char& c : rows)
            c = ' ';
    }

    for (char &i : tracker)
        i = ' ';
}

// Main starting point
void TicTacToe :: start() {

    int n = 0;

    while (n != 10) {
        
        this -> initialization();

        cout << endl << " Choose game mode : " << endl;
        
        cout << endl << " -> Enter 1 to play single player." << endl;
        cout << " -> Enter 2 to play double player" << endl;
        cout << " -> Enter 10 to exit." << endl;
        cout << endl << " *** Be careful when inputing anything. Invalid input will cause an exception and eventually the program will be terminated. ***" << endl << endl;
    
        cout << " Input here : ";
        cin >> n;

        if (n == 1)
            this -> singlePlay();

        else if (n == 2)
            this -> doubleplay();

        else if (n == 10)
            cout << " Program exited." << endl;

        else
            throw INPUT_INVALIDATION_EXCEPTION();
    }
}

// Handle single player game mode
void TicTacToe :: singlePlay() {

    string name;

    cout << endl << " Enter player name : ";
    cin >> name;

    cout << endl << " -> Enter alphabet X (case insensitive) to play first using X." << endl;
    cout << " -> Enter alphabet O (case insensitive) to play after CPU's turn finishes using O." << endl << endl;

    cout << " Input here : ";

    char c;
    cin >> c;

    if (c == 'X' || c == 'x')
        this -> singlePlayerProcessor('X', name);

    else if (c == 'O' || c == 'o')
        this -> singlePlayerProcessor('O', name);
    
    else
        throw INPUT_INVALIDATION_EXCEPTION();
}

void TicTacToe :: singlePlayerProcessor(char sign, string playerName) {

    string name1 = (sign == 'X') ? playerName : "CPU";
    string name2 = (sign == 'O') ? playerName : "CPU";

    cout << endl << " " << name1 << " will play first using X." << endl;
    cout << " " << name2 << " will play using O after " << name1 << "'s turn finishes." << endl;

    cout << endl << " " << "This is the main table to play : " << endl;

    this -> displayMainTable();

    
    for (int i = 1; i <= 9; i++) {

        if (i % 2 == 1) {
            
            int temp = (sign == 'X') ? this -> turn_singlePlayer('X', playerName) : this -> turn_CPU('X','O');

            if (temp == 1)
                return;
        }

        else {

            int temp = (sign == 'O') ? this -> turn_singlePlayer('O', playerName) : this -> turn_CPU('O','X');

            if (temp == 1)
                return;
        }
    }

    cout << " Match Drawn." << endl << endl;
}

int TicTacToe :: turn_singlePlayer(char sign, string playerName) {

    this -> displayAssistance();

    cout << endl << " " << playerName << "'s turn to put an " << sign << " in : ";

    int index;

    cin >> index;

    if (index < 1 || index > 9)
        throw INPUT_INVALIDATION_EXCEPTION();

    while (tracker[index] != ' ') {

        cout << " " << index << " is already filled. Put an " << sign << " again in : ";
        cin >> index;

        if (index < 1 || index > 9)
            throw INPUT_INVALIDATION_EXCEPTION();
        }

    this -> updateTable(index, sign);

    this -> displayMainTable();

    if (this -> determineResult(sign) == true) {

        cout << " " << playerName << " won the match." << endl << endl;
        return 1;
    }
    return 0;
}

// Simulate CPU's turn
int TicTacToe :: turn_CPU(char cpuSign, char playerSign) {

    int index;
    vector<int> vec;

    if (filledCount <= 1) {

        srand((unsigned) time(0));
        index = rand() % 9 + 1;

        while (tracker[index] != ' ')
            index = rand() % 9 + 1;
    }

    if (
        tracker[5] == cpuSign && tracker[9] == cpuSign && tracker[1] == ' ' ||
        tracker[2] == cpuSign && tracker[3] == cpuSign && tracker[1] == ' ' ||
        tracker[4] == cpuSign && tracker[7] == cpuSign && tracker[1] == ' '
        )
        index = 1;
    
    else if (
        tracker[5] == cpuSign && tracker[8] == cpuSign && tracker[2] == ' ' ||
        tracker[1] == cpuSign && tracker[3] == cpuSign && tracker[2] == ' '
        )
        index = 2;

    else if (
        tracker[1] == cpuSign && tracker[2] == cpuSign && tracker[3] == ' ' ||
        tracker[6] == cpuSign && tracker[9] == cpuSign && tracker[3] == ' ' ||
        tracker[5] == cpuSign && tracker[7] == cpuSign && tracker[3] == ' '
        )
        index = 3;

    else if (
        tracker[5] == cpuSign && tracker[6] == cpuSign && tracker[4] == ' ' ||
        tracker[1] == cpuSign && tracker[7] == cpuSign && tracker[4] == ' '
        )
        index = 4;
    
    else if (
        tracker[1] == cpuSign && tracker[9] == cpuSign && tracker[5] == ' ' ||
        tracker[3] == cpuSign && tracker[7] == cpuSign && tracker[5] == ' ' ||
        tracker[4] == cpuSign && tracker[6] == cpuSign && tracker[5] == ' ' ||
        tracker[2] == cpuSign && tracker[8] == cpuSign && tracker[5] == ' '
        )
        index = 5;
    
    else if (
        tracker[4] == cpuSign && tracker[5] == cpuSign && tracker[6] == ' ' ||
        tracker[3] == cpuSign && tracker[9] == cpuSign && tracker[6] == ' '
        )
        index = 6;

    else if (
        tracker[3] == cpuSign && tracker[5] == cpuSign && tracker[7] == ' ' ||
        tracker[8] == cpuSign && tracker[9] == cpuSign && tracker[7] == ' ' ||
        tracker[1] == cpuSign && tracker[4] == cpuSign && tracker[7] == ' '
        )
        index = 7;

    else if (
        tracker[7] == cpuSign && tracker[9] == cpuSign && tracker[8] == ' ' ||
        tracker[2] == cpuSign && tracker[5] == cpuSign && tracker[8] == ' '
        )
        index = 8;

    else if (
        tracker[1] == cpuSign && tracker[5] == cpuSign && tracker[9] == ' ' ||
        tracker[7] == cpuSign && tracker[8] == cpuSign && tracker[9] == ' ' ||
        tracker[3] == cpuSign && tracker[6] == cpuSign && tracker[9] == ' '
        )
        index = 9;

    else if (
        tracker[5] == playerSign && tracker[9] == playerSign && tracker[1] == ' ' ||
        tracker[2] == playerSign && tracker[3] == playerSign && tracker[1] == ' ' ||
        tracker[4] == playerSign && tracker[7] == playerSign && tracker[1] == ' '
        )
        index = 1;
    
    else if (
        tracker[5] == playerSign && tracker[8] == playerSign && tracker[2] == ' ' ||
        tracker[1] == playerSign && tracker[3] == playerSign && tracker[2] == ' '
        )
        index = 2;

    else if (
        tracker[1] == playerSign && tracker[2] == playerSign && tracker[3] == ' ' ||
        tracker[6] == playerSign && tracker[9] == playerSign && tracker[3] == ' ' ||
        tracker[5] == playerSign && tracker[7] == playerSign && tracker[3] == ' '
        )
        index = 3;

    else if (
        tracker[5] == playerSign && tracker[6] == playerSign && tracker[4] == ' ' ||
        tracker[1] == playerSign && tracker[7] == playerSign && tracker[4] == ' '
        )
        index = 4;
    
    else if (
        tracker[1] == playerSign && tracker[9] == playerSign && tracker[5] == ' ' ||
        tracker[3] == playerSign && tracker[7] == playerSign && tracker[5] == ' ' ||
        tracker[4] == playerSign && tracker[6] == playerSign && tracker[5] == ' ' ||
        tracker[2] == playerSign && tracker[8] == playerSign && tracker[5] == ' '
        )
        index = 5;
    
    else if (
        tracker[4] == playerSign && tracker[5] == playerSign && tracker[6] == ' ' ||
        tracker[3] == playerSign && tracker[9] == playerSign && tracker[6] == ' '
        )
        index = 6;

    else if (
        tracker[3] == playerSign && tracker[5] == playerSign && tracker[7] == ' ' ||
        tracker[8] == playerSign && tracker[9] == playerSign && tracker[7] == ' ' ||
        tracker[1] == playerSign && tracker[4] == playerSign && tracker[7] == ' '
        )
        index = 7;

    else if (
        tracker[7] == playerSign && tracker[9] == playerSign && tracker[8] == ' ' ||
        tracker[2] == playerSign && tracker[5] == playerSign && tracker[8] == ' '
        )
        index = 8;

    else if (
        tracker[1] == playerSign && tracker[5] == playerSign && tracker[9] == ' ' ||
        tracker[7] == playerSign && tracker[8] == playerSign && tracker[9] == ' ' ||
        tracker[3] == playerSign && tracker[6] == playerSign && tracker[9] == ' '
        )
        index = 9;

    else if (tracker[5] == cpuSign) {
        
        if (tracker[1] == ' ')
            vec.push_back(1);

        if (tracker[2] == ' ')
            vec.push_back(2);

        if (tracker[3] == ' ')
            vec.push_back(3);
        
        if (tracker[4] == ' ')
            vec.push_back(4);

        if (tracker[5] == ' ')
            vec.push_back(5);

        if (tracker[6] == ' ')
            vec.push_back(6);

        if (tracker[7] == ' ')
            vec.push_back(7);

        if (tracker[8] == ' ')
            vec.push_back(8);

        if (tracker[9] == ' ')
            vec.push_back(9);
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[1] == cpuSign) {

        if (tracker[2] == ' ') {
            vec.push_back(2);

            if (tracker[3] == ' ')
                vec.push_back(3);
        }

        if (tracker[4] == ' ') {
            vec.push_back(4);

            if (tracker[7] == ' ')
                vec.push_back(7);
        }

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[9] == ' ')
                vec.push_back(9);
        }
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[3] == cpuSign) {

        if (tracker[2] == ' ') {
            vec.push_back(2);

            if (tracker[1] == ' ')
                vec.push_back(1);
        }

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[7] == ' ')
               vec.push_back(7);
        }

        if (tracker[6] == ' ') {
            vec.push_back(6);

            if (tracker[9] == ' ')
                vec.push_back(9);
        }
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[7] == cpuSign) {
        
        if (tracker[4] == ' ') {
            vec.push_back(4);

            if (tracker[1] == ' ')
                vec.push_back(1);
        }

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[3] == ' ')
                vec.push_back(3);
        }

        if (tracker[8] == ' ') {
            vec.push_back(8);

            if (tracker[9] == ' ')
                vec.push_back(9);
        }
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[9] == cpuSign) {

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[1] == ' ')
                vec.push_back(1);
        }

        if (tracker[6] == ' ') {
            vec.push_back(6);

            if (tracker[3] == ' ')
                vec.push_back(3);
        }

        if (tracker[8] == ' ') {
            vec.push_back(8);

            if (tracker[7] == ' ')
                vec.push_back(7);
        }

        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
        
        return index;
    }

    else if (tracker[2] == cpuSign) {

        if (tracker[1] == ' ')
            vec.push_back(1);

        if (tracker[3] == ' ')
            vec.push_back(3);

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[8] == ' ')
                vec.push_back(8);
        }
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
        
        return index;
    }

    else if (tracker[4] == cpuSign) {
        
        if (tracker[1] == ' ')
            vec.push_back(1);

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[6] == ' ')
                vec.push_back(6);
        }

        if (tracker[7] == ' ')
            vec.push_back(7);
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[6] == cpuSign) {
        
        if (tracker[3] == ' ')
            vec.push_back(3);

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[4] == ' ')
                vec.push_back(4);
        }

        if (tracker[9] == ' ')
            vec.push_back(9);
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    else if (tracker[8] == cpuSign) {

        if (tracker[5] == ' ') {
            vec.push_back(5);

            if (tracker[2] == ' ')
                vec.push_back(2);
        }

        if (tracker[7] == ' ')
            vec.push_back(7);

        if (tracker[9] == ' ')
            vec.push_back(9);
        
        int r;

        srand((unsigned) time(0));

        if (vec.size() > 0)
            r = rand() % (vec.size()-1);

        index = vec[r];
    }

    cout << endl << " CPU's turn to put an " << cpuSign << " in : " << index << endl;

    this -> updateTable(index, cpuSign);

    this -> displayMainTable();

    cout << endl << " CPU has put an " << cpuSign << " in " << index << endl << endl ;

    if (this -> determineResult(cpuSign) == true) {

        cout << " CPU won the match." << endl << endl;
        return 1;
    }
    return 0;
}

// Handle double player game mode
void TicTacToe :: doubleplay() {

    string name1, name2;

    cout << endl << " First player name : ";
    cin >> name1;
    cout << " Second player name : ";
    cin >> name2;

    cout << endl << " " << name1 << " will play first using X." << endl;
    cout << " " << name2 << " will play using O after " << name1 << "'s turn finishes." << endl;

    cout << endl << " " << "This is the main table to play : " << endl;

    this -> displayMainTable();

    for (int i = 1; i <= 9; i++) {

        if (i % 2 == 1) {
            
            int temp = this -> doublePlayerProcessor(name1, name2, 1);

            if (temp == 1)
                return;
        }

        else {
            int temp = this -> doublePlayerProcessor(name1, name2, 2);

            if (temp == 1)
                return;
        }
    }

    cout << " Match Drawn." << endl << endl;
}

// Take players input and proccess from double player mode
int TicTacToe :: doublePlayerProcessor(string name1, string name2, int i) {

    string name = (i == 1) ? name1 : name2;
    char sign = (i == 1) ? 'X' : 'O';

    this -> displayAssistance();

    cout << endl << " " << name << "'s turn to put an " << sign << " in : ";

    int index;

    cin >> index;

    if (index < 1 || index > 9)
        throw INPUT_INVALIDATION_EXCEPTION();

    while (tracker[index] != ' ') {

        cout << " " << index << " is already filled. Put an " << sign << " again in : ";
        cin >> index;

        if (index < 1 || index > 9)
            throw INPUT_INVALIDATION_EXCEPTION();
        }

        this -> updateTable(index, sign);

        this -> displayMainTable();

        if (this -> determineResult(sign) == true) {

            cout << " " << name << " won the match." << endl << endl;
            return 1;
        }
        return 0;
}

// Display the main playing table
void TicTacToe :: displayMainTable() {

    cout << endl;

    for (int i = 0; i < 3; i++) {
        
        cout << "\t";

        for (int j = 0; j < 3; j++) {

            cout << mainTable[i][j];
            
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

// Display an input assistance table which shows the indexes
void TicTacToe :: displayAssistance() {
    
    cout << " For index assistance : " << endl << endl;

    for (int i = 1; i < 10; i++) {

        if (i == 1 || i == 4 || i == 7)
            cout << "\t";

        cout << i;

        if (i % 3 == 0)
            cout << endl;
        
        else
            cout << " | ";
    }
}

// Update table after taking player input
void TicTacToe :: updateTable(int index, char sign) {

    tracker[index] = sign;

    if (index >= 1 && index <= 3)
        mainTable[0][index-1] = sign;

    else if (index >= 4 && index <= 6)
        mainTable[1][index-4] = sign;

    else if (index >= 7 && index <= 9)
        mainTable[2][index-7] = sign;

    filledCount++;
}

// // Determine if any player won the match
bool TicTacToe :: determineResult(char sign) {

    if (
        (tracker[1] == sign && tracker[5] == sign && tracker[9] == sign) ||
        (tracker[3] == sign && tracker[5] == sign && tracker[7] == sign) ||
        (tracker[1] == sign && tracker[2] == sign && tracker[3] == sign) ||
        (tracker[4] == sign && tracker[5] == sign && tracker[6] == sign) ||
        (tracker[7] == sign && tracker[8] == sign && tracker[9] == sign) ||
        (tracker[1] == sign && tracker[4] == sign && tracker[7] == sign) ||
        (tracker[2] == sign && tracker[5] == sign && tracker[8] == sign) ||
        (tracker[3] == sign && tracker[6] == sign && tracker[9] == sign)
        )
        return true;
    
    return false;
}