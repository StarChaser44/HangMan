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
	std::vector<char> correctLetters;
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
		std::cout << "Here is the word: " + wordInPlay << " You didn't have to cheat! "<< std::endl;
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

	const bool letterGuess(char userLetter) {
		std::size_t found = wordInPlay.find(userLetter);
		if (found == std::string::npos) {
			--guesses;
			if (guesses == 0) inGame = false;
			nonPlayableLetters.push_back(userLetter);
			return false;
		}
		else {
			if (found > 0) {
				correctLetters.push_back(userLetter);
				unsigned int count{0};
				for (unsigned int i = 0; i < correctLetters.size(); ++i) {
					if (userLetter == correctLetters.at(i)) {
						(++count);
					}
				}
				if (count > 1) {
					std::cout << "You already played that character, try again. No Penalty." << std::endl;
					correctLetters.pop_back();
				}
				
			}
			
			return true;
		}
	}

	void printArray() {
		for (int i = 0; i < correctLetters.size(); ++i) {
			std::cout << correctLetters.at(i) << " ";
		}
	}

	const void printWord() {
		bool found{ false };
		for (std::size_t i = 0; i < wordInPlay.size(); ++i) {
			for (std::size_t j = 0; j < correctLetters.size(); ++j) {
				if (wordInPlay.at(i) == correctLetters.at(j)) {
					std::cout << correctLetters.at(j) << " " << std::endl;
					found = true;
				}
				else {
					found = false;
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

	std::cout << "Weclome to hang man, this game will be pretty easy. Here are the commands required to play the game. Enjoy!" << std::endl;
	std::cout << "You have a " << game.getWordLength() << " letter word" << std::endl;
	menu();
	int choice;
	std::cout << "Enter a choice: ";
	std::string userWord;
	char letter;
	std::cin >> choice;
	while (game.winner() != true && game.isInGame() == true) {
		switch (choice) {
		case 1:
			game.printWord();
			std::cout << "Enter a word: " << std::endl;
			std::cin >> userWord;
			if (!game.userWordGuess(userWord)) {
				std::cout << "Sorry, that guess was incorrect, you now have" << game.getGuesses() << " guesses left" <<std::endl;
			}
			else {
				std::cout << "Congrats, you win!";
			}
			break;
		case 2:
			game.printWord();
			std::cout << "Enter a letter: " << std::endl;
			std::cin >> letter;
			if (!game.letterGuess(letter)) {
				std::cout << "Sorry, that guess was incorrect, you now have" << game.getGuesses() << " guesses left" << std::endl;
			}
			else {
				std::cout << "That's correct, keep going!" << std::endl;
			}
			break;
		case 3:
			game.cheat();
			didCheat = true;
			break;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
		game.printArray();

		if (game.winner() == false) {
			menu();
			if (choice == 1) {
				std::cout << "Guess again or choose another option: ";
			}
			else if (choice == 2) {
				std::cout << "Guess another letter or choose another option: ";
			}
			else {
				std::cout << "Choose another option: ";
			}
			std::cin >> choice;
		}
	}
	//delete letter;

	//std::cout << " Exiting game" << std::endl;
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
