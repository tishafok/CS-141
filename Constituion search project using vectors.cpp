//Frantishek Akulich
//CS141 Project#4
//UIN 663378893
//3.22.2020


#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

//Function to lower each line of constitution
string lowerString (string lineToLower){
    string NewString;
    for (int i=0; i < lineToLower.length(); i++){
        NewString.push_back(tolower(lineToLower.at(i)));
    }
    return NewString;
}

//Function to lower the input word or phrase to be searched for
char* lowerChar (char* lineToLower){
    for (int i=0; i< strlen(lineToLower); i++){
        lineToLower[i] = tolower(lineToLower[i]);
    }
    return lineToLower;
}

//Function to load constitution and return number of lines in it
int loadConstitution (vector<string>& constitution, int constLines) {
    ifstream inStream;
    string line;
    inStream.open("ConstitutionAndBillOfRights.txt");
    if (!inStream.is_open()) {
        cout << "Could not find txt file.  Exiting..." << endl;
        exit(-1);
    }
    while (getline(inStream, line)) {
        if (line.size() > 1) {
            constLines++;
            constitution.push_back(line);
        }
    }
    inStream.close();
    return constLines;
}

//Function that searches the word or phrase, returns int array
//That lists all lines where it was found

int* findWord(vector<string> &constitution, char* phrase, int constLines, int lineFoundAt[10]){
    string tempLow;
    int lineFoundCount =0;
    for (int i=0; i< constLines; i++){
        //Temporary lower the constitution line for comparison
        tempLow = lowerString(constitution.at(i));

        //If found, assign line number to first array element
        if (tempLow.find(phrase) != string::npos){
            lineFoundAt[lineFoundCount] = i;
            lineFoundCount ++;
        }
    }
    return lineFoundAt;
}

//Function that displays given line
void lineDisplay(vector<string> &constitution, int lineFoundAt){
    cout << endl << "Line " << lineFoundAt << ": " << endl
         << constitution.at(lineFoundAt) << endl;
}



int main() {

vector<string> constitution;
int constLines;
char userAction;
int max_length = 100;
char phrase[max_length];
int lineFound[10];
char returnCharacter;

//Initialize array that stores word or phrase occurrences with
//values of -1 so it's not within bounds of existing line numbers
for (int i=0; i < 10; i++){
    lineFound[i] = -1;
    }

//Load constitution txt file into string vector
//Return number of lines
constLines = loadConstitution (constitution, constLines);

//Set first menu options
cout << "Select from the following choices: " << endl
<< "   " << "W  Enter word or phrase to find, and display enclosing text " << endl
<< "   " << "X  Exit program " << endl << "Your choice: ";

//Prompt initial user input
cin >> userAction;
returnCharacter = cin.get();
userAction = tolower(userAction);

//First menu
switch(userAction) {
    case 'w':
        cout << endl << "Enter word or phrase: ";
        cin.getline(phrase, max_length);

        //Lower the phrase or word to be looked for
        lowerChar(phrase);

        //Find word or phrase and display its first instance
        findWord(constitution, phrase, constLines, lineFound);
        lineDisplay(constitution, lineFound[0]);

        //Set second menu options
        while (userAction != 'x') {
            cout << endl << "Select from the following choices: " << endl
                 << "   " << "W  Enter word or phrase to find, and display enclosing text " << endl
                 << "   " << "P  Display previous text " << endl
                 << "   " << "F  Display following text " << endl
                 << "   " << "A  Display all occurrences of found word or phrase " << endl
                 << "   " << "X  Exit program " << endl << "Your choice: ";

            //Prompt user input
            cin >> userAction;
            returnCharacter = cin.get();
            userAction = tolower(userAction);

            //Second menu
            switch (userAction) {

                //Find and display another word or phrase
                case 'w':
                    cout << endl << "Enter word or phrase: ";
                    cin.getline(phrase, max_length);
                    lowerChar(phrase);
                    findWord(constitution, phrase, constLines, lineFound);
                    lineDisplay(constitution, lineFound[0]);
                    break;

                //Display previous line of text
                case 'p':
                    if (lineFound[0] > 0){
                        --lineFound[0];
                        lineDisplay(constitution, lineFound[0]);
                    }

                    //Condition to not go before line 0
                    else if (lineFound[0] == 0){
                        cout << "There is no previous file contents. " << endl;
                    }
                    break;

                //Display next line of text
                case 'f':
                    if (lineFound[0] <constLines-1){
                        ++lineFound[0];
                        lineDisplay(constitution, lineFound[0]);
                    }

                    //Condition to not go past last line of text
                    else if (lineFound[0] == constLines-1){
                        cout << "There is no following file contents. " << endl;
                    }
                    break;

                //Display all occurrences of word or phrase searched for
                case 'a':

                    //Loop through array that saves line numbers of searched instances
                    //And display each one

                    for (int i=0; i< (sizeof(lineFound)/ sizeof(lineFound[0])); i++) {
                        if (((lineFound[i]) >= 0) && (lineFound[i] < constLines)) {
                            lineDisplay(constitution, lineFound[i]);
                        }
                    }
                    break;
            }
        }
        cout << "Exiting program." << endl;
        break;

    //Exit condition
    case 'x':
        cout << endl << "Exiting program." << endl;
        exit(0);
}
return 0;
}
