#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map //again unreal friendly

using int32 = int;


FBullCowGame::FBullCowGame() //Default constructor
{
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {4,7},{5,10},{6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::GetHiddenWord(int32 length) {
	
	//this must be an isogram
	FString HIDDEN_WORD = "";

	if (length == 4)
	{
		HIDDEN_WORD = "chin";
	}
	else if (length == 5)
	{
		HIDDEN_WORD = "court";
	}
	else
	{
		HIDDEN_WORD = "planet";
	}
	MyHiddenWord = HIDDEN_WORD;
	return;
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess))//if guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowerCase(Guess))//if guess isn't all lower case  
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
	
}


//recieves a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;


	// loop through all letters in guess
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 GChar = 0; GChar < WordLength; GChar++) {
		// compare letters against the hidden word
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			//if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar] && GChar == MHWChar) {
				//increment bulls if they're in the same place
				BullCowCount.Bulls++;
			}
			else if (Guess[GChar] == MyHiddenWord[MHWChar] && GChar != MHWChar) {
				//increment cows if not.
				BullCowCount.Cows++;
			}
				
				
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {return true;}

	//setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { 
			return false; // DO NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}

	}			


	return true; // in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;;
}
