// Turing Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const char BLANK = 'B';
const char ZERO = '0';
const char ONE = '1';
const char STAR = '*';
const char LEFT = 'L';
const char RIGHT = 'R';
const int MAXTAPE = 100;
const int MAXSTATES = 25;
const int MAXLENGTH = 40;
const short STARTPOS = 40;
const char STARTSTATE = ZERO;
const int MAXTUPLES = 100;
const int TUPLELENGTH = 5;

struct tape {
    char value;
    int position;
    tape* leftPtr;
    tape* rightPtr;
};

int main()
{
    ifstream input;
    string inputName;

    tape* newSlide;
    tape* head;
    tape* currentSlide = NULL;
    tape* temp;
    tape* lastBlank = NULL; // Points to the slide right before the first char of the string

    char theString[MAXLENGTH] = { 0 }; // The initial string
    char theTuples[MAXTUPLES][TUPLELENGTH];
    int length = 0; // The length of the initial string

    int tupleAmount = 0;
    int currentTuple = 0;

    int slidePosition = 1;

    char currentState = '0';
    int highlightedSpot = 0;

    bool validateString = 1;

    newSlide = new tape;
    newSlide->value = BLANK;
    newSlide->position = slidePosition;
    head = newSlide;
    currentSlide = newSlide;
    newSlide->leftPtr = NULL;

    while (slidePosition <= MAXTAPE) {
        newSlide = new tape;
        newSlide->value = BLANK;
        newSlide->position = slidePosition + 1;
        currentSlide->rightPtr = newSlide;
        newSlide->leftPtr = currentSlide;
        currentSlide = newSlide;
        slidePosition++;
    }

    newSlide->rightPtr = NULL;

    cout << "Enter the name of the file with the tuples. => ";
    cin >> inputName;

    input.open(inputName);

    if (input.fail()) {
        cout << "There was an error with opening the file!" << endl;
        return 1;
    }

    //input >> theString;
    cout << "Enter the input string. => ";
    cin >> theString;


    cout << "Would you like to validate the string (check if tape head returns to original spot)?" << endl;
    cout << "1 for yes, 0 for no. => ";
    cin >> validateString;

    for (length = 0; theString[length] != '\0'; length++);

    for (int i = 0; i < MAXTUPLES; i++) {
        for (int j = 0; j < TUPLELENGTH; j++) {
            input >> theTuples[i][j];
            if (input.fail()) {
                tupleAmount = i;
                i = MAXTUPLES;
                j = TUPLELENGTH;
            }
        }
    }

    cout << "Tape starts at " << STARTPOS << ". The length is " << length << " and the highlighted position is " << STARTPOS << endl;
    temp = head;
    while (temp->rightPtr != NULL) {
        if (temp->position == STARTPOS - 1) {
            lastBlank = temp;
            cout << temp->value << " ";
            for (int i = 0; i < length; i++) {
                temp = temp->rightPtr;
                temp->value = theString[i];
                if (i == 0) {
                    currentSlide = temp;
                    cout << "|" << temp->value << "| ";
                }
                else {
                    cout << temp->value << " ";
                }
            }
            temp = temp->rightPtr;
            cout << temp->value << endl;
        }
        else {
            temp = temp->rightPtr;
        }
    }

    for (int i = 0; i < tupleAmount; i++) {
        if (theTuples[i][0] == currentState && theTuples[i][1] == currentSlide->value) {
            for (int j = 0; j < tupleAmount; j++) {
                cout << j + 1 << ": ";
                for (int k = 0; k < TUPLELENGTH; k++) {
                    cout << theTuples[j][k] << " ";
                }
                cout << endl;
            }
            cout << "Tuple " << i + 1 << " applies." << endl;
            currentState = theTuples[i][2];
            currentSlide->value = theTuples[i][3];
            if (theTuples[i][4] == 'R') {
                currentSlide = currentSlide->rightPtr;
            }
            else {
                currentSlide = currentSlide->leftPtr;
            }
            i = -1;
            highlightedSpot = currentSlide->position;
            temp = lastBlank;
            cout << endl;
            for (int l = 0; l <= length + 1; l++) {
                if (highlightedSpot == temp->position) {
                    cout << "|" << temp->value << "| ";
                }
                else {
                    cout << temp->value << " ";
                }
                temp = temp->rightPtr;
            }
            cout << endl;
        }
    }

    cout << "Execution halts in state " << currentState << endl;
    cout << "Tape starts at " << STARTPOS << ". The length is " << length << " and the highlighted position is " << highlightedSpot << endl;

    if (validateString) {

        if (highlightedSpot == STARTPOS) {
            cout << "This string is validated!" << endl;
        }
        else {
            cout << "This string is invalid!" << endl;
        }

    }

    input.close();

    return 0;

}