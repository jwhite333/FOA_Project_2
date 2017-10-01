#pragma once
#include <map>
#include <string>

// Suit names
enum suit
{
	DIAMONDS = 0,
	CLUBS,
	HEARTS,
	SPADES,
	NUM_SUITS
};

// Suit name pairings
std::map<suit, std::string> suitName
{
	{ DIAMONDS, "Diamonds" },
	{ CLUBS, "Clubs" },
	{ HEARTS, "Hearts" },
	{ SPADES, "Spades" }
};

// Function to return string representation of card suits
std::string getSuitName(suit suit)
{
	auto it = suitName.find(suit);
	if (it == suitName.end())
		return "Invalid Suit";
	else
		return it->second;
}

// Card value pairings
std::map<int, std::string> valueName
{
	{ 1, "Ace" },
	{ 11, "Jack" },
	{ 12, "Queen" },
	{ 13, "Kings" },
};

// Function to return string representations of card values
std::string getValueName(int value)
{
	auto it = valueName.find(value);
	if (it == valueName.end())
		return std::to_string(value);
	else
		return it->second;
}