//
// This is a solution of classic Desk of Cards problem. 
//
// Author: Maoxu Li
// Date: Apr 14, 2012
// Email: li@maoxuli.com
//

#include "cards.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdlib.h>

//
// Class: Card
//

Card::Card()
{
	
}

Card::Card(int rank, SUIT suit) : 
	_rank(rank),
	_suit(suit)
{
	
}

Card::~Card()
{
	
}

void Card::set(int rank, SUIT suit)
{
	_rank = rank;
	_suit = suit;
}

int Card::rank()
{
	return _rank;
}

Card::SUIT Card::suit()
{
	return _suit;
}

//
// Class: Deck
//

Deck::Deck()
{	
	// Todo: exception handling
	initialize();
}

Deck::~Deck()
{
	// Clear
	for(CardSeq::iterator it = _cards.begin(); it != _cards.end(); ++it)
	{
		Card* p = *it;
		assert(p != NULL);
		delete p;
	}
	_cards.clear();
	std::cout << "Deck of cards is clear and destructed.\n";
}

// Initialize 52 cards with rank from 1 to 13 and 
// suits of hearts, spades, clubs, diamonds
// Todo: Exception handling
bool Deck::initialize()
{
	for(int i=0; i<13; ++i)
	{
		// * We did not use loop on the value of SUIT here
		//   to remove the dependence of their predefined values
		_cards.push_back(new Card(i+1, Card::HEART));
		_cards.push_back(new Card(i+1, Card::SPADE));
		_cards.push_back(new Card(i+1, Card::CLUB));
		_cards.push_back(new Card(i+1, Card::DIAMOND));
		
		// Otherwise
		//for(int j=0; j<4; ++j)
		//{
		//	_cards.push_back(new Card(i+1, j));
		//}
	}
	
	// Reset interator for dealing cards
	_iterator = _cards.begin();
	
	std::cout << "A deck of cards (52 cards) is initialized.\n";
	return true;
}

// Shuffle with swap algorithm
void Deck::shuffle()
{
	// Initialize for rand()
	srand(static_cast<int>(time(NULL)));

	int n = _cards.size();
	for(int i=n-1; i>0; --i)
	{
		std::swap(_cards[i], _cards[rand() % (i+1)]);
	}

	// Reset interator for dealing cards
	_iterator = _cards.begin();
	
	std::cout << "Cards are shuffled a round.\n";
}

// Deal one card
// The instance of Deck will not change its size between 
// constructs and destruction, using iterator is safe here.
// (Using index otherwise)
Card* Deck::deal_one_card()
{
	if(_iterator == _cards.end())
	{
		return NULL;
	}
	
	return *_iterator++;
}
