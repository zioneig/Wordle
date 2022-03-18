/* Zion Eig-Tassiello
* 3/1/2022
* This is the game of Wordle, guess the correct word and you win
*/

#include<iostream>
#include<fstream>
#include<string>
#include<time.h>

using namespace std;

void LoadWords(string fName, string wordList[], int numWords);

void DisplayCurrent(string currBoard, int guessesUsed);

bool GuessWord(string wordList[], int numWords, string guess);

bool CheckWin(string correctWord, string gues);

string CheckChars(string correctWord, string guess);




int main() {


	srand(time(0));
	cout << "Welcome to Wordle\n";

	ifstream inFile;
	inFile.open("words.txt");

	string throwAway;
	int numWords = 0;

	//read file once to get word amount
	while (getline(inFile, throwAway)) {
		numWords++;
	}

	inFile.close();

	string* wordList = new string[numWords];

	LoadWords("words.txt", wordList, numWords);


	//game start
	char playAgain;
	int guessesUsed;
	bool hasWon;
	string currBoard; //all previous guesses
	string guess;


	do {

		currBoard = "";
		guessesUsed = 0;
		hasWon = false;

		string correctWord = wordList[rand() % numWords];

		while (guessesUsed < 6 && !hasWon) {
			do
			{
				cout << "What word would you like to guess?\n";
				getline(cin, guess);

			} while (!GuessWord(wordList, numWords, guess));

			currBoard += guess + "\n";
			currBoard += CheckChars(correctWord, guess);

			DisplayCurrent(currBoard, guessesUsed);

			hasWon = CheckWin(correctWord, guess);
			if (hasWon) {
				cout << "Congrats, You Won!\n";
			}


			guessesUsed++;
		}

		if (!hasWon) {
			cout << "Sorry, you lost\n";
		}

		cout << "The correct word was: " << correctWord << endl;


		cout << "Another game? y or n";
		cin >> playAgain;
		cin.ignore();

	} while (playAgain == 'y');

	cout << "Thank you!\n";

	return 0;
}

//fills wordList[] with words from the file
void LoadWords(string fName, string wordList[], int numWords) {
	ifstream inFile;

	inFile.open(fName);

	//opens file again to load word array
	for (int i = 0; i < numWords; i++) {
		getline(inFile, wordList[i]);
	}

	inFile.close();

	cout << "Your file was imported!\n";
	cout << numWords << " word imported.\n";

}

//displays the current guesses
void DisplayCurrent(string currBoard, int guessesUsed) {
	
	cout << currBoard;

	for (int i = 0; i < 6 - guessesUsed-1; i++) {
		cout << "-----" << endl;
	}

}

//returns false if word is not in word list, true if is
bool GuessWord(string wordList[], int numWords, string guess) {

	for (int i = 0; i < numWords; i++) {
		if (wordList[i] == guess)
			return true;
	}

	cout << "This word is not in the list.\n";
	return false;
}

//returns true if words are equivalent, false if not
bool CheckWin(string correctWord, string guess) {
	return correctWord == guess;
}

//creates string that tells user which letters are correct and which are somewhere else in the word
string CheckChars(string correctWord, string guess) {

	string toReturn = "_____\n";

	for (int i = 0; i < 5; i++) {
		if (correctWord[i] == guess[i])
			toReturn[i] = '!';

		else {
			for (int j = 0; j < 5; j++) {
				if (j != i && correctWord[j] == guess[i])
					toReturn[i] = '&';
			}
		}
	}

	return toReturn;
}