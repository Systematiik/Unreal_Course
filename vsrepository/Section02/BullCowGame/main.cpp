/*This is the console executable, that makes use of the BullCow class
  This acts as the view in a MVC pattern, and is responsible for all user
  interaction. For game logic, see the FBullCowGame class.
 */

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make syntax 'Unreal' friendly
using FText = std::string;
using int32 = int;

//Prototype methods to allow accesibility
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText ReturnGuess(FText PrintGuess);
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //Instantiate a new game

//Entry point for our application
int main() {

	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true);

	//Exits the application
	return 0;
}

//Introdues the game to the user
void PrintIntro() {
	int32 HiddenWordLength = BCGame.GetHiddenWordLength();

	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "***Bull: When a letter is in the right place.***" << std::endl;
	std::cout << "***Cow: When a letter is right but in the wrong place.***" << std::endl;
	std::cout << std::endl;
	std::cout << "Can you guess the " << HiddenWordLength;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

//Asks the player if they want to play again
bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same word? (y/n) \n\n";
	FText Response = "";
	std::getline(std::cin, Response);

	if ((Response[0] == 'y') || (Response[0] == 'Y')) {
		std::cout << std::endl;
		return true;
	}
	else if((Response[0] == 'n') || (Response[0] == 'N')){
		return false;
	}
	else {
		return false;
	}
}

//Plays a single game until completion
void PlayGame() {
	BCGame.Reset();
	int32 MyMaxTries = BCGame.GetMaxTries();

	//loop for the number of turns is NAUGHT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MyMaxTries) {

		//submit valid guess to the game, and receive counts
		GetValidGuess();
		std::cout << std::endl;
	}

	PrintGameSummary();//TODO add a game summary
	return;

}

//Lets player know if they've won or lost
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You have won the game!\n";
	} else {
		std::cout << "Bad luck, try again next time!\n";
	}
	return;
}

//loop until player gets a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << MyCurrentTry << " of " << BCGame.GetMaxTries() << " "; 
		std::cout << "Enter a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n" << std::endl;
			break;
		case EGuessStatus::NOT_Isogram:
			std::cout << "Please enter a word without repeating letters.\n" << std::endl;
			break;
		case EGuessStatus::NOT_Lowercase:
			std::cout << "Please enter a lowercase word.\n" << std::endl;
			break;
		default:
			break;//assume the guess is valid
		} 
	} while (Status != EGuessStatus::OK); //keep looping until no errors

	return ReturnGuess(Guess);
}

//Prints the guess back to them
FText ReturnGuess(FText PrintGuess) {
	//Submit valid guess to the game
	FBullCowCount BullCowCount = BCGame.SubmitValidGuess(PrintGuess);

	std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << std::endl;

	return PrintGuess;
}