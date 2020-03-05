/* Prog3Vigenere.cpp
 *     Encode/Decode using Vigenere cipher.
 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>
using namespace std;

const int DICT_SIZE = 21735;
const int WORD_SIZE = 82;
int numberOfWords = 0;


bool compare(char dictionary1[DICT_SIZE][WORD_SIZE], char* userWord) {
    bool compareResult;
    for (int i = 0; i < DICT_SIZE; i++) {
        if (strcmp(dictionary1[i], userWord) == 0) {
            compareResult = true;
            break;
        } else {
            compareResult = false;
        }
    }
    return compareResult;
}

char* getInput(char* arrayIn, char* arrayOut) {
    int index = 0;
    fgets(arrayIn, WORD_SIZE, stdin);
    while (arrayIn[index] != '\n') {
        arrayIn[index] = tolower(arrayIn[index]);
        index++;
    }
    strncpy(arrayOut, arrayIn, index);
    return arrayOut;
}

char* adjustKeyword(char* text, char* keyword, char* keywordAdjusted) {
    char keywordExpanded[WORD_SIZE];
    strcpy(keywordExpanded, keyword);
    while (strlen(keywordExpanded) < WORD_SIZE) {
        strcat(keywordExpanded, keyword);
    }
    strncpy(keywordAdjusted, keywordExpanded, strlen(text));
    return keywordAdjusted;
}

int indexLocate(char text, char* letterArray2) {
    int indexFound = 0;
    for (int i = 0; i < strlen(letterArray2); i++) {
        if (text == letterArray2[i]) {
            indexFound = i;
            break;
        }
    }
    return indexFound;
}


char* encodeText (char* text, char* keyword, char* cipherText, char vigenereTable[25][26], char* letterArray2) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] != ' ') {
            cipherText[i] = vigenereTable[indexLocate(keyword[i],
                                                      letterArray2)][indexLocate(text[i], letterArray2)];
        } else {
            cipherText[i] = ' ';
        }
    }
    return cipherText;
}

char* decodeText (char* keyword2, char* givenCode, char* originalText, char vigenereTable[25][26], char* letterArray2){
    int index2 = 0;
    for (int z=0; z<strlen(givenCode); z++) {
        for (int i = 0; i < 26; i++) {
            if (givenCode[z] == vigenereTable[indexLocate(keyword2[z], letterArray2)][i]) {
                index2 = i;
                break;
            }
        }
        if (givenCode[z] != ' ') {
            originalText[z] = letterArray2[index2];
        }
        else {
            originalText[z] = ' ';
        }
    }
    return originalText;
}




//---------------------------------------------------------------------------
int main()
{
    // Declare variables
    int menuOption;                   // Userinput for menu option
    char returnCharacter;             // Separately store the return character so cin.getline does not consider it the next user input
    char userWord[WORD_SIZE];
    char dictionary[DICT_SIZE][WORD_SIZE];
    char theWord[WORD_SIZE];
    char inputArray[WORD_SIZE];
    char textToEncode[WORD_SIZE];
    char keyword[WORD_SIZE];
    char keywordAdjusted[WORD_SIZE];
    char cipherText[WORD_SIZE];
    char textToDecode[WORD_SIZE];
    char originalText[WORD_SIZE];

    ifstream inStream;
    inStream.open("dictionary.txt");
    if (!inStream.is_open()) {
        cout << "Could not find dictionary.txt.  Exiting..." << endl;
        exit(-1);
    }
    while (inStream >> theWord) {
        if (strlen(theWord) >= 3) {
            strncpy(dictionary[numberOfWords], theWord, strlen(theWord) + 1);
            numberOfWords++;
        }
    }
    inStream.close();

    char letterArray[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char vigenereTable[25][26] = {0};
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26 - i; j++) {
            vigenereTable[i][j] = letterArray[j + i];
            for (int z = 0; z < i; z++) {
                vigenereTable[i][26 - i + z] = letterArray[z];
            }
        }
    }
    char letterArray2[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    cout << numberOfWords << " words of size >= 3 were read in from dictionary. \n" << endl;

    // Display menu and handle menu options
    cout << "Choose from the following options: \n"
         << "    1. Lookup dictionary word \n"
         << "    2. Encode some text  \n"
         << "    3. Decode some text  \n"
         << "    4. Auto-decode the ciphertext given with the assignment  \n"
         << "    5. Exit program  \n"
         << "Your choice: ";
    cin >> menuOption;
    returnCharacter = cin.get();  // Read and discard the return character at the end of the above input line.
    // This is necessary because otherwise a subsequent cin.getline() reads it as
    // an empty line of input.
    switch( menuOption) {
        case 1: // Do dictionary lookup of a word and indicate whether or not it was found.
            cout << "Enter a word to be looked up in dictionary: ";
            cin.getline(userWord, WORD_SIZE);
                if (compare(dictionary, userWord)){
                    cout << userWord << " IS in the dictionary." << endl;
                }
                else {
                    cout << userWord << " is NOT in the dictionary." << endl;
                }
        break;


        case 2: // Encode some text

            cout << "Enter the text to be encoded: ";
            getInput(inputArray, textToEncode);

            cout << "Enter a keyword for Vigenere encryption: ";
            getInput(inputArray, keyword);

            adjustKeyword(textToEncode, keyword, keywordAdjusted);
            cout << "Keyword, plainText and ciphertext are:  \n";
            cout << keywordAdjusted << endl << textToEncode << endl;
            cout << encodeText (textToEncode, keywordAdjusted, cipherText, vigenereTable, letterArray2) << endl;

            break;

        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            getInput(inputArray, textToDecode);
            cout << "Enter a Vigenere keyword to be tried: 3 words found using keyword: ";
            getInput(inputArray, keyword);
            cout << keyword << " giving:" << endl;

            adjustKeyword(textToDecode, keyword, keywordAdjusted);

            cout << "   " << decodeText (keywordAdjusted, textToDecode, originalText, vigenereTable, letterArray2) << endl;
            break;

        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";

            break;

        case 5: // exit program
            cout << "Exiting program" << endl;
            exit( 0);
            break;

        default:
            // Sanity check
            cout << "Invalid menu option.  Exiting program." << endl;
            break;
    }// end switch( menuOption)

    return 0;
}//end main()
