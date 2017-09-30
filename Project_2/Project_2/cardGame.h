#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "d_node.h"

enum suit
{
	DIAMOND = 0,
	CLUB,
	HEART,
	SPADE
};

class card
{
private:
	int cardValue;
	int cardSuit;
public:
	card(){}

	//copy constrcutor for card
	card(const card &other)
	{
		cardValue = other.cardValue;
		cardSuit = other.cardSuit;
	}

	int getCardValue()
	{
		return cardValue;
	}

	int getCardSuit()
	{
		return cardSuit;
	}

	void setCardValue(int value)
	{
		cardValue = value;
	}

	void setCardSuit(int suit)
	{
		cardSuit = suit;
	}


};

class deck
{
private:
	node<card> *pokerDeck;
	node<card> *temp;
	node<card> *temp2;
	node<card> *firstCard;
	node<card> *lastCard;
	node<card> *newNext;
public:

	//generate a deck of card
	deck()
	{
		pokerDeck = NULL;
		int cardIndex = 1;
		int suitIndex = 0;
		// call class card to generate a card and put in link list deck 
		for (int index = 1; index < 53; index++)
		{
			temp = new node<card>;
			card newcard;
			if (index == 14 || index == 27 || index == 40) {
				cardIndex = 1;
				suitIndex++;
			}
			newcard.setCardValue(cardIndex);
			newcard.setCardSuit(suit(suitIndex));

			temp->nodeValue = newcard;
			temp->next = pokerDeck;

			pokerDeck = temp;

			cardIndex++;

		}
	}

	deck(const deck& pokerDeck) {

	}

	void print()
	{
		temp = new node<card>;
		temp = pokerDeck;
		int cardNumber;
		std::string suitType;

		//print out the card in the current deck
		while (temp != nullptr)
		{
			//loop through the dead
			for(int index=1; index<=52; index++)
			{
				switch (temp->nodeValue.getCardSuit())
				{
				case 0:
					suitType = "DIAMOND";
					break;
				case 1:
					suitType = "CLUB";
					break;
				case 2:
					suitType = "HEART";
					break;
				case 3:
					suitType = "SPADE";
					break;
				}
				cardNumber = temp->nodeValue.getCardValue();
				if (cardNumber == 13 || cardNumber == 12 ||
					cardNumber == 11 || cardNumber == 1)
				{
					if (cardNumber == 13) {
						std::cout << "King" << " " << suitType << std::endl;
						temp = temp->next;
					}
					else if (cardNumber == 12) {
						std::cout << "Queen" << " " << suitType <<std::endl;
						temp = temp->next;
					}

					else if (cardNumber == 11)
					{
						std::cout << "Jack" << " " << suitType << std::endl;
						temp = temp->next;
					}

					else
					{
						std::cout << "Ace" << " " << suitType << std::endl;
						temp = temp->next;
					}
				}
				else
				{
					std::cout << temp->nodeValue.getCardValue() << " " << suitType << std::endl;
					temp = temp->next;
				}
			}
			
			
		}
		std::cout << std::endl;
	}

	
	card deal()
	{
		std::string suitType;

		//remove it from the deck
		temp = new node<card>;
		firstCard = new node<card>;

		temp= pokerDeck;
		firstCard->nodeValue = pokerDeck->nodeValue;

		//move the next card up
		temp= pokerDeck->next;
		pokerDeck = temp;

		//put the first card at the bottom of the deck
		replace(firstCard->nodeValue);

		//return the card the was deal
		return firstCard->nodeValue;
	}

	//place the first card at the bottom of the deck
	void replace(card cardToReplace)
	{
		temp = new node<card>;
		temp2 = new node<card>;
		lastCard = new node<card>;

		lastCard->nodeValue = cardToReplace;
		temp = pokerDeck;

		//loop until it is last card in the deck
		while (temp->next != NULL)
		{
			temp2 = temp->next;
			temp = temp2;
			
		}
		//point the next card to the last card
		temp->next = lastCard;
	}

	void shuffle()
	{
		int cardPlace;
		temp = new node<card>;
		temp2 = new node<card>;
		temp = pokerDeck;
		//shuffle the deck, 100 time moving the card
		for (int index = 0; index < 99; index++) 
		{
			//pick a random card place in the deck
			srand((int)time(NULL));
			cardPlace = rand() % 52 + 5;

			for (int j=0; j < cardPlace; j++)
			{
				if (temp->next != NULL) {
					//store the previous node
					temp2 = temp;
					
					temp = temp->next;

					//next node
					newNext = temp->next;
				}
			}

			//place the slect card to the top
			temp2->next = newNext;
			temp->next = pokerDeck;
			pokerDeck = temp;
		}
	}

};