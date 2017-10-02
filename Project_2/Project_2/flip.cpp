/*
* Name: Jun Jie Chen, Jon White
* Project 2
* Group: 5
* Platform: Microsoft Visual Studio
*/

#include <iostream>
#include "cardGame.h"

enum inputError
{
	NONE,
	NOT_A_CHAR,
	NOT_F_OR_G
};

bool getKeyboardInput()
{
	// Get user input
	char input;
	inputError error;
	do
	{
		try
		{
			// Ask user to enter the guess number;
			std::cout << "Please enter \"f\" to take a card, or \"g\" to end the game with your current score" << std::endl;
			std::cin >> input;

			// Catch bad input
			if (std::cin.fail())
				throw inputError::NOT_A_CHAR;

			// Catch out of range input
			if (input != 'f' && input != 'g')
				throw inputError::NOT_F_OR_G;

			error = inputError::NONE;
		}
		catch (inputError e)
		{
			// Set error flag
			error = e;

			// Display error for bad input
			if (e == inputError::NOT_A_CHAR)
				std::cout << "ERROR, input not a char" << std::endl;
			if (e == inputError::NOT_F_OR_G)
				std::cout << "ERROR, input is not one of the available options" << std::endl;

			// Clear cin buffer
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		}

	} while (error != inputError::NONE);

	// Check if the user wanted to flip another card or end the game
	if (input == 'f')
		return true;
	else
		return false;
}

void updateScore(card flippedCard, int & score)
{
	switch (flippedCard.getCardValue())
	{
		case 1: // Ace
		{
			score += 10;
			break;
		}
		case 11: // Jack
		case 12: // Queen
		case 13: // King
		{
			score += 5;
			break;
		}
		case 8:
		case 9:
		case 10:
		{
			break;
		}
		case 7:
		{
			score = score / 2;
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		{
			score = 0;
			break;
		}
	}

	// Check for a heart
	if (flippedCard.getCardSuit() == HEARTS)
	{
		score += 1;
	}
}

// Play the game
void playFlip()
{
	// Play the game Flip
	deck deck;
	deck.shuffle();
	int score = 0;
	bool keepPlaying = true;

	std::cout << "Welcome to Flip!" << std::endl << std::endl <<
		"Take a card to begin" << std::endl;

	do
	{
		// Check to make sure there are still cards left (if replace is not used)
		if (deck.size <= 0)
		{
			std::cout << "There are no more cards left in the deck! The game is over!" << std::endl;
			break;
		}
		// Run game mechanics
		keepPlaying = getKeyboardInput();
		if (keepPlaying)
		{
			// Flip a card
			card flippedCard = deck.deal();
			std::cout << "Flipping a card.." << std::endl << 
				"Your card is: " << flippedCard.printToString();

			// Modify score based on flipped card
			updateScore(flippedCard, score);
			std::cout << "Your new score is: " << score << std::endl;

			// Replace the card
			deck.replace(flippedCard);
		}

	} while (keepPlaying);

	std::cout << "Your final score is: " << score << std::endl;
}


int main()
{
	playFlip();
	system("pause");
	return 0;
}
