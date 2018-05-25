/* The game logic (no view code or direct user interaction)
 * The game is a simple guess the word game based on Mastermind
 */

#pragma once
#include <string>

//To make syntax 'Unreal' friendly
using FString = std::string;
using int32 = int;


//All values initialized to 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	NOT_Isogram,
	NOT_Lowercase,
	Wrong_Length
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	void Reset(); 
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity (FString) const; //TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for values
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};