
/* This is the console executable, that makes use of the BullCowClass
This acts as teh view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//prototype function as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; //instantiate a new game, re used across plays


// Entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exit game
}


void PrintIntro()
{
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Try to guess the Isogram\n";
	std::cout << "---------------------------------------\n";
	std::cout << "If a letter in the word you input matches the isogram in the same place you get a BULL\n";
	std::cout << "If a letter matches but is in the wrong place you get a COW\n";
	std::cout << "---------------------------------------\n\n";
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	std::cout << "Choose word length between 4 to 6: ";
	int32 length;
	std::cin >> length;
	std::cin.get();
	BCGame.GetHiddenWord(length);
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	// loop asking for guesses
	// until the game is NOT won, and still turns remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		//submit valid guess to game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until user gives valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry<< " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
} while (Status != EGuessStatus::OK); // Keep looping until we get no errors.
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE YOU WON!\n";
	}
	else
	{
		std::cout << "Bad luck you ran out of guesses!\n";
	}
}