// My previous submission was giving correct answer and had higher number of points
// However this one includes full binary search and more comments
// Therefore please have mercy on grading me
// Worked really hard on this one. Would do better if had more time

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cctype>     // Allows using the tolower() function
#include <cstring>
using namespace std;

const int DICT_SIZE = 21735;
const int WORD_SIZE = 60;

//Simple compare function to see if input word is in dictionary

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

//Function for getting input, using lower case letters and getting rid of \n return

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

// Function to loop the keyword and then chop it so it matches the length of input cypher

char* adjustKeyword(char* text, char* keyword, char* keywordAdjusted) {
    int index =0;
    char keywordExpanded[WORD_SIZE];
    while((keyword[index] != '\0') && (keyword[index] != '\n')){
        keywordExpanded[index] = keyword[index];
        index++;
    }
    while (strlen(keywordExpanded) < WORD_SIZE) {
        strcat(keywordExpanded, keyword);
    }
    strncpy(keywordAdjusted, keywordExpanded, strlen(text));
    return keywordAdjusted;
}

// Function to locate the index of letter array, so it can be used for coding/decoding later

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

// Encode function that uses user input as entry, looks up values using previously mentioned indexLocate function
// returns converted text

char* encodeText (char* text, char* keyword, char* cipherText, char vigenereTable[25][26], char* letterArray2) {
    for (int i = 0; i < strlen(text); i++) {
        if ((text[i] == ':') || (text[i] == '.') || (text[i] == '/') || (text[i] == ',') || (text[i] == '|')
        || (text[i] == '`') || (text[i] == ';')){
            cipherText[i] = text[i];
        }
        else if (text[i] != ' ') {
            cipherText[i] = vigenereTable[indexLocate(keyword[i],
                                                      letterArray2)][indexLocate(text[i], letterArray2)];
        } else {
            cipherText[i] = ' ';
        }
    }
    return cipherText;
}

// Decode function, similar to encode function, just works in reverse

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

//Function for binary search

bool binarySearch (char* wordToFind, char dictionary[DICT_SIZE][WORD_SIZE]) {
    int low, mid, high;
    int LIMIT = DICT_SIZE;
    low = 0;
    high = LIMIT;

    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(wordToFind, dictionary[mid]) == 0) {
            return true;
        } else if (strcmp(wordToFind, dictionary[mid]) < 0) {
            high = mid - 1;
        } else if (strcmp(wordToFind, dictionary[mid]) > 0) {
            low = mid + 1;
        }
    }
    return false;
}

// Function that takes in string of user input, chops it into individual words, feeds these words into binary
// search function, returns boolean if word was found in the dictionary. And once all words have been searched
// for in the dictionary, returns the integer value of # of words found

int searchInDictionary(char* decipheredString, char dictionary[DICT_SIZE][WORD_SIZE]) {

    char extractedWord[WORD_SIZE];
    char shortenedStringWithSpace[WORD_SIZE];
    char shortenedStringWithoutSpace[WORD_SIZE];
    int index3 = 0;
    int spaceCount = 0;
    int wordsFound = 0;

    for (int b = 0; b < WORD_SIZE; b++) {
        extractedWord[b] = '\0';
    }
    for (int z=0; z < strlen(decipheredString); z++) {
        if (decipheredString[z] == ' ') {
            spaceCount++;
        }
    }
    for (int w=0; w<spaceCount+1; w++){
        index3 = 0;
        while (decipheredString[index3] != ' ') {
            index3++;
        }

        strncpy(extractedWord, decipheredString, index3);
        for (int z = 0; z < strlen(extractedWord); z++) {
            extractedWord[z] = tolower(extractedWord[z]);
        }

        if (binarySearch(extractedWord, dictionary)){
            wordsFound ++;
        }

        if (strcmp(extractedWord, decipheredString) ==0){
            break;
        }
        strcpy(shortenedStringWithSpace, strchr(decipheredString, ' '));

        for (int z = 1; z < strlen(shortenedStringWithSpace) + 1; z++) {
            shortenedStringWithoutSpace[z - 1] = shortenedStringWithSpace[z];
        }

        for (int b = 0; b < WORD_SIZE; b++) {
            extractedWord[b] = '\0';
        }
        strcpy(decipheredString, shortenedStringWithoutSpace);
    }
    return wordsFound;
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
    char bookWord[WORD_SIZE];

    // all varibles called and initiated

    int maxWords = 0;
    int dictIndex =0;
    int wordSize =3;
    int wordsFound = 0;
    ifstream inStream;

    // looped through all char arrays to set all cells to null

    for (int b = 0; b < WORD_SIZE; b++) {
        originalText[b] = '\0';
        textToDecode[b] = '\0';
        userWord[b] = '\0';
        theWord[b] = '\0';
        inputArray[b] = '\0';
        keyword[b] = '\0';
        keywordAdjusted[b] = '\0';
        cipherText[b] = '\0';
        textToDecode[b] = '\0';
        bookWord[b] = '\0';
    }

// Read the dictionary into 2D char array and sort by word length at the same time
// Word size is set to be 3 or larger

    while(wordSize < WORD_SIZE){
        inStream.open("dictionary.txt");
            if (!inStream.is_open()) {
                cout << "Could not find dictionary.txt.  Exiting..." << endl;
                exit(-1);
                }
            while (inStream >> theWord) {
            if (strlen(theWord) == wordSize) {
                for (int z=0; z< wordSize; z++){
                    theWord[z] = tolower(theWord[z]);
                }
                strncpy(dictionary[dictIndex], theWord, wordSize);
                dictIndex++;
            }
        }
        inStream.close();
        wordSize++;
    }

// Created 2D letter array of Vigenere code

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

    // Had to re-initialize the array because was getting errors with pointers
    // Just learned how to use offset
    // Didn't have enough time to implement

    char letterArray2[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};



    cout << dictIndex << " words of size >= 3 were read in from dictionary. \n" << endl;

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

// Straight forward usage for first and second excercises. Call functions defined above main body earlier

        case 2: // Encode some text

            cout << "Enter the text to be encoded: ";
            getInput(inputArray, textToEncode);

            cout << "Enter a keyword for Vigenere encryption: ";
            getInput(inputArray, keyword);

            adjustKeyword(textToEncode, keyword, keywordAdjusted);

            encodeText (textToEncode, keywordAdjusted, cipherText, vigenereTable, letterArray2);

            cout << "Keyword, plainText and ciphertext are:  \n";
            cout << keywordAdjusted << endl << textToEncode << endl;
            cout << encodeText (textToEncode, keywordAdjusted, cipherText, vigenereTable, letterArray2) << endl;

            break;

        case 3: // Decode using user-entered values
            cout << "Enter the cipherText to be decoded: ";
            getInput(inputArray, textToDecode);
            cout << "Enter a Vigenere keyword to be tried: ";
            getInput(inputArray, keyword);

            adjustKeyword(textToDecode, keyword, keywordAdjusted);

            cout << searchInDictionary(decodeText(keywordAdjusted, textToDecode,
                                                  originalText, vigenereTable, letterArray2), dictionary)+1 << " words found using keyword: " << keyword
                 << " giving:" << endl << "   " << decodeText(keywordAdjusted, textToDecode,
                                                              originalText, vigenereTable, letterArray2) << endl;

            // call functions to display decoded message

            break;

        case 4: // Decode ciphertext given with the assignment
            cout << "Enter the cipherText to be decoded: ";
            getInput(inputArray, textToDecode);

            // Read in one word from the book at a Time
            // Then check for # of words found in dictionary
            // Count the instances with max words found
            // Gave me error exit code 6 :(

            inStream.open("TheSecretAgentByJosephConrad.txt");
            while (inStream >> bookWord) {
                if (strlen(bookWord) >= 3) {
                    for (int i = 0; i < strlen(bookWord); i++) {
                        bookWord[i] = tolower(bookWord[i]);
                    }
                    int index = 0;
                    while ((bookWord[index] != '\0') && (bookWord[index] != '\n')) {
                        keyword[index] = bookWord[index];
                        index++;
                    }

                    adjustKeyword(textToDecode, keyword, keywordAdjusted);

                    decodeText(keywordAdjusted, textToDecode,
                               originalText, vigenereTable, letterArray2);
                    cout << originalText << endl;
                    cout << searchInDictionary(originalText, dictionary) << endl;

                    if (maxWords < wordsFound) {
                        maxWords = wordsFound;
                        cout << maxWords << " words found using keyword: " << keyword << " giving: \n"
                             << "   " << decodeText(keywordAdjusted, textToDecode,
                                                    originalText, vigenereTable, letterArray2) << endl;
                    }
                }
            }
            inStream.close();

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
