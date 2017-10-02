#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "cardNames.h"
#include "node.h"

#define SHUFFLE_ITERATIONS 100
#define MIN_CARD_VALUE 1
#define MAX_CARD_VALUE 13

class card
{
private:
	int cardValue;
	suit cardSuit;
public:
	card(){}

	// Copy constrcutor for card
	card(const card &otherCard)
	{
		cardValue = otherCard.cardValue;
		cardSuit = otherCard.cardSuit;
	}

	// Constructor
	card(int value, suit suit)
	{
		cardValue = value;
		cardSuit = suit;
	}

	bool operator == (const card &otherCard)
	{
		if (cardValue == otherCard.cardValue && cardSuit == otherCard.cardSuit)
			return true;
		else
			return false;
	}

	// Overloaded assignment operator
	void operator = (const card &otherCard)
	{
		cardValue = otherCard.cardValue;
		cardSuit = otherCard.cardSuit;
	}

	int getCardValue()
	{
		return cardValue;
	}

	suit getCardSuit()
	{
		return cardSuit;
	}

	void setCardValue(int value)
	{
		cardValue = value;
	}

	void setCardSuit(suit suit)
	{
		cardSuit = suit;
	}

	void print()
	{
		std::cout << getValueName(cardValue) << " of " << getSuitName(cardSuit) << std::endl;
	}

	std::string printToString()
	{
		std::stringstream stream;
		stream << getValueName(cardValue) << " of " << getSuitName(cardSuit) << std::endl;
		return stream.str();
	}

};

// Redefining linked list node name for convenience
typedef node<card> * node_ptr;
typedef card * card_ptr;

class deck
{
private:
	node_ptr topCard;

public:
	int size;

	// Generate a deck of cards
	deck()
	{
		topCard = NULL;

		// Call class card to generate a card and put in link list deck
		for (int newSuit = (int)DIAMONDS; newSuit <= (int)SPADES; newSuit++)
		{
			for (int newValue = MIN_CARD_VALUE; newValue <= MAX_CARD_VALUE; newValue++)
			{
				// Create a new card
				card_ptr newCard = new card(newValue, (suit)newSuit);

				// Put the new card on top of the deck
				node_ptr newNode = new node<card>(newCard, topCard);

				// Set the new card as the top card
				topCard = newNode;

				// Increase the deck size
				size++;
			}
		}
	}

	// Not sure what this is used for
	deck(const deck& pokerDeck) {
		topCard = pokerDeck.topCard;
		size = pokerDeck.size;
	}

	// Print the deck
	void print()
	{
		node_ptr currentCard = topCard;

		while (currentCard != NULL)
		{
			std::cout << getValueName(currentCard->value->getCardValue()) << " of " << getSuitName(currentCard->value->getCardSuit()) << std::endl;

			// Move to next card
			currentCard = currentCard->next;
		}
		std::cout << "Size: " << size << std::endl;
	}

	// Re-introduce a card at the end of the deck after it has been dealt
	void replace(card cardToReplace)
	{
		// Find the end of the deck
		node_ptr currentCard = topCard;
		while (currentCard->next != NULL)
		{
			currentCard = currentCard->next;
		}

		// Create a new node and add it to the list
		card_ptr lastCard = new card(cardToReplace);
		node_ptr newLast = new node<card>(lastCard, NULL);
		currentCard->next = newLast;

		// Increase deck size
		size++;
	}

	// Return the top card from the deck, and remove it from the deck
	card deal()
	{
		// Return the top card and remove it from the deck
		card firstCard = *topCard->value;

		node_ptr temp = topCard->next;

		// Remove the top card from the deck, and set the new topCard pointer to the second card
		delete topCard;
		topCard = temp;

		// Decrease size by 1
		size--;

		return firstCard;
	}

	// Place a specific card at the bottom of the deck
	void moveCardToBottom(card cardToMove)
	{
		// Find card, while keeping track of precious card
		node_ptr previousCard = NULL;
		node_ptr currentCard = topCard;
		node_ptr lastCard = NULL;

		while (currentCard->next != NULL)
		{
			// Check to see if we have found the correct card
			if (*currentCard->value == cardToMove)
			{
				lastCard = currentCard;

				// Check for top card
				if (lastCard == topCard)
					topCard = currentCard->next;
				break;
			}

			// Move forward one node
			previousCard = currentCard;
			currentCard = currentCard->next;
		}

		// Modify the list to remove the selected card
		if (previousCard != NULL)
			previousCard->next = currentCard->next;

		// Find the end of the list
		while (currentCard->next != NULL)
		{
			currentCard = currentCard->next;
		}

		// Add the card again to the end of the list
		if (lastCard != NULL)
		{
			lastCard->next = NULL;
			currentCard->next = lastCard;
		}
		else
		{
			throw "Could not locate the card to be replaced";
		}		
	}

	void shuffle()
	{
		// Shuffle the deck by replacing random cards 100 times
		srand((int)time(NULL));
		for (int index = 0; index < SHUFFLE_ITERATIONS; index++)
		{
			// Pick a random card place in the deck
			int cardPosition = rand() % ((int)NUM_SUITS * (int)MAX_CARD_VALUE - 1); // 51, since the last card moving would not change the deck order

			// Traverse the list cardPosition times
			node_ptr currentCard = topCard;
			for (int j = 0; j < cardPosition; j++)
			{
				currentCard = currentCard->next;
			}

			// Use moveCardToBottom to put the card at the end of the deck
			if (currentCard != NULL)
			{
				try
				{
					moveCardToBottom(*currentCard->value);
				}
				catch (std::string exception)
				{
					std::cout << "ERROR!: " << exception << std::endl;
				}
			}
		}
	}

};