// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

class HangMan {
private:
	std::string wordInPlay;
	std::vector<std::string> playableWords{ "fox", "catch" "attack", "smack" };
	std::vector<char> nonPlayableLetters;
	std::vector<char> playedLetters;
	bool inGame;
	bool didWin{ false };
	uint8_t guesses{ 6 };


public:
	HangMan() {
		inGame = true;
		initWordInPlay();
	}
	void addWords(std::string word) {
		std::cout << "Added the word " << word << std::endl;
		playableWords.push_back(word);
	}
	const int getGuesses() {
		return guesses;
	}
	void initWordInPlay() {
		srand(time(NULL));
		int randomIndex = rand() % playableWords.size();
		wordInPlay = playableWords.at(randomIndex);
	}
	const void cheat() {
		std::cout << "Here is the word: " + wordInPlay << "You didn't have to cheat! "<< std::endl;
	}
	
	const std::string getWord() {
		return wordInPlay;
	}

	const bool isInGame() {
		return inGame;
	}

	const bool winner() {
		return didWin;
	}

	const size_t getWordLength() {
		return wordInPlay.size();
	}

	const bool userWordGuess(std::string userGuess) {
		if (userGuess.compare(wordInPlay) == 0) {
			didWin = true;
			return true;
		}
		else {
			--guesses;
			if (guesses < 1) inGame = false;
			return false;
		}
	}

	const bool letterGuess(char* userLetter) {
		std::size_t found = wordInPlay.find(*userLetter);
		if (found == std::string::npos) {
			--guesses;
			if (guesses < 1) inGame = false;
			nonPlayableLetters.push_back(*userLetter);
			return false;
		}
		else {
			int index = -1;
			for (int i = 0; i < playedLetters.size(); ++i) {
				if (*userLetter == playedLetters.at(i)) {
					index = i;
				}
			}
			if (index == -1) {
				playedLetters.push_back(*userLetter);
			}
			else {
				std::cout << "You already played that character, try again. No Penalty." << std::endl;
			}
			return true;
		}
	}

	const void printWord() {
		bool found{ false };
		char letter;
		for (std::size_t i = 0; i < wordInPlay.size(); ++i) {
			for (std::size_t j = 0; j < playedLetters.size(); ++j) {
				if (wordInPlay.at(i) == playedLetters.at(j)) {
					std::cout << wordInPlay.at(i) << " " << std::endl;
					found = true;
					letter = wordInPlay.at(i);
				}
			}
			if (!found) {
				std::cout << "_ ";
			}
		}
		std::cout << "" << std::endl;
	}
	
};
void menu() {
	std::cout << "1. Guess the entire word" << std::endl;
	std::cout << "2. Guess a letter from the word" << std::endl;
	std::cout << "3. Cheat" << std::endl;

}
int main()
{
	bool didCheat{ false };
	HangMan game;
	while (!game.winner() && game.isInGame()) {
		std::cout << "Weclome to hang man, this game will be pretty easy. Here are the commands required to play the game. Enjoy!" << std::endl;
		std::cout << "You have a " << game.getWordLength() << " letter word" << std::endl;
		menu();
		int choice;
		std::cout << "Enter a choice: ";
		std::string* userWord{ nullptr };
		char* letter{ nullptr };
		std::cin >> choice;
		switch (choice) {
		case 1:
			game.printWord();
			std::cout << "Enter a word: " << std::endl;
			//std::string* userWord{ nullptr };
			std::cin >> *userWord;
			if (!game.userWordGuess(*userWord)) {
				std::cout << "Sorry, that guess was incorrect, you now have" << game.getGuesses() << " guesses left" <<std::endl;
			}
			// userWord;
			break;
		case 2:
			game.printWord();
			std::cout << "Enter a letter: " << std::endl;
			//char* letter{ nullptr };
			std::cin >> *letter;
			if (!game.letterGuess(letter)) {
				std::cout << "Sorry, that guess was incorrect, you now have" << game.getGuesses() << " guesses left" << std::endl;
			}
			else {
				std::cout << "That's correct, keep going!" << std::endl;
			}
			//delete letter;
			break;
		case 3:
			game.cheat();
			didCheat = true;
			break;
		}
		delete userWord;
		delete letter;
	
	}
	if (game.winner()) {
		if (didCheat) {
			std::cout << "This doesn't count. Try again without cheating!" << std::endl;
		}
		else {
			std::cout << "Congratulations, you won! Go eat a cookie now." << std::endl;
		}
	}
	else {
		std::cout << "Sorry, you were not able to win. Try again at another date." << std::endl;
		std::cout << "The correct word was " << game.getWord() << std::endl;
	}

	system("pause");
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
