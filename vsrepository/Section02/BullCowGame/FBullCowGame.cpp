#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <map>

//To make syntax 'Unreal friendly'
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {Reset();}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return int32(MyHiddenWord.length());}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,5}, {5,5}, {6,8} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
	constexpr int MAX_TRIES = 5;

	const FString HIDDEN_WORD = "tony"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	bGameIsWon = false;

	MyCurrentTry = 1;
	return;
}

//Used to check if the player's guess is an isogram
bool FBullCowGame::IsIsogram(FString Word) const {
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	//setup our map
	TMap<char, bool> LetterSeen;

	//loop through all the letters of the word
	for (auto Letter : Word) { //for all letters of the word
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false; //we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true;
		}
	}
			//add the letter to the map as seen

	return true; //for example in cases where "/0" is entered
}

//Checks if a letter is lowercase in the player's guess
bool FBullCowGame::IsLowercase(FString Word) const {
	//loop through all the letters of the word
	for (auto Letter : Word) { //for all letters of the word
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

//Used to check the validity of the player's guess through a series of steps
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::NOT_Isogram; //if the guess isn't an isogram
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::NOT_Lowercase; //if the guess isn't all lowercase
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length; //if the guess length is wrong
	}
	else {
		return EGuessStatus::OK; //Otherwise, return OK
	}
}

//Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	//Loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//Compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//If the match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {//If they're in the same place
					BullCowCount.Bulls++; //Increment Bulls
				}
				else{
					BullCowCount.Cows++;//Increment cows if not
				}
			}
		}
		if (BullCowCount.Bulls == WordLength) {
			bGameIsWon = true;
		}
		else {
			bGameIsWon = false;
		}
	}
	return BullCowCount;
}