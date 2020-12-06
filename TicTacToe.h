#include<iostream>

using namespace std;

#ifndef TicTacToe_H
#define TicTacToe_H

class TicTacToe {

    private:

    int filledCount; // Count filled places of main table
    char mainTable[3][3]; // Main table for playing
    char tracker[10]; // To track game progress

    void initialization(); // Preparing everything

    void singlePlay(); // Handle single player game mode
    void singlePlayerProcessor(char sign, string playerName); // Processor for single player game mode
    int turn_singlePlayer(char sign, string name); // Handle player input in single player mode
    int turn_CPU(char cpuSign, char playerSign); // Simulate CPU's turn

    void doubleplay(); // Handle double player game mode
    int doublePlayerProcessor(string name1, string name2, int i); // Processor for double player game mode

    void displayMainTable(); // Display the main playing table
    void displayAssistance(); // Display an input assistance table which shows the indexes
    
    void updateTable(int index, char sign); // Update table with players input
    bool determineResult(char sign); // Determine if any player won the match

    public:

    void start(); // Main starting point
};

#endif