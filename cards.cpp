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

//
// Class: Card
//

Card::Card(int rank, SUIT suit) : 
	_rank(rank),
	_suit(suit)
{
	
}

Card::~Card()
{
	
}

int Card::rank()
{
	return _rank;
}

SUIT Card::suit()
{
	return _suit;
}

//
// Class: Deck
//

#define DEFAULT_SHUFFLE_ROUNDS 20
Deck::Deck(int rounds) :
	_shuffle_rounds(rounds)
{
	// Shuffle rounds
	if(_shuffle_rounds <= 0)
	{
		_shuffle_rounds = DEFAULT_SHUFFLE_ROUNDS;
	}
	
	// Initialize 52 cards with rank from 1 to 13 and 
	// suits of hearts, spades, clubs, diamonds
	// Todo: Exception handling
	for(int i=0; i<13; ++i)
	{
		// * We did not use loop on the value of SUIT here
		//   to remove the dependence of their predefined values
		_cards.push_back(new Card(i+1, HEART));
		_cards.push_back(new Card(i+1, SPADE));
		_cards.push_back(new Card(i+1, CLUB));
		_cards.push_back(new Card(i+1, DIAMOND));
	}
	
	_iterator = _cards.begin();
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
	std::cout << "Deck is clear and destructed.\n";
}

void Deck::shuffle()
{
	// Initialize for rand()
	srand(time(NULL));
	
	int round = _shuffle_rounds;
	int n = _cards.size();
	while(round-- > 0)
	{
		for(int i=n-1; i>0; --i)
		{
			std::swap(_cards[i], _cards[rand() % (i+1)]);
		}
	}
	std::cout << "Shuffle " << _shuffle_rounds << " rounds.\n";
}

// Deal one card
// The instance of Deck will not change its size between 
// constructs and destruction, using iterator is safe here.
// Using index otherwise
Card* Deck::deal_one_card()
{
	if(_iterator == _cards.end())
	{
		return NULL;
	}
	
	return *_iterator++;
}

void Deck::dump()
{
	std::cout << "Deck of cards:\n";
	int n = _cards.size();
	for(int i=0; i<n; ++i)
	{
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << _cards[i]->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "(" << _cards[i]->suit() << ")"
		<< ((i+1) % 4 == 0 ? "\n" : "\t\t");
	}
	std::cout << std::endl;
}
