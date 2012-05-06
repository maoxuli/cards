//
// This is a solution of classic Desk of Cards problem. 
// V2
//
// Author: Maoxu Li
// Date: May 5, 2012
// Email: li@maoxuli.com
//

#include "cards.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdlib.h>

//
// Class: DefaultCard
//

DefaultCard::DefaultCard(int rank, Card::SUIT suit) :
	_rank(rank),
	_suit(suit)
{
	
}

DefaultCard::~DefaultCard()
{
	
}

int DefaultCard::rank()
{
	return _rank;
}

Card::SUIT DefaultCard::suit()
{
	return _suit;
}

void DefaultCard::draw()
{
	// Todo: draw card on screen
	std::cout << "This is a card with DEFAULT_CARD_STYLE\n";
}

//
// CardFactory
//

// Singleton instance
DefaultCardFactory* DefaultCardFactory::_instance  = NULL;

DefaultCardFactory::DefaultCardFactory()
{
	
}

DefaultCardFactory::~DefaultCardFactory()
{
	
}

DefaultCardFactory* DefaultCardFactory::instance()
{
	// Lazy init
	if(_instance == NULL)
	{
		_instance = new DefaultCardFactory();
	}
	
	assert(_instance != NULL);
	return _instance;
}

Card* DefaultCardFactory::create(int rank, Card::SUIT suit)
{
	return new DefaultCard(rank, suit);
}

//
// Class: Deck
//

Deck* Deck::_instance = NULL;

Deck::Deck(CARD_STYLE style) :
	_style(style)
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

// Get single instance of Deck
Deck* Deck::instance(CARD_STYLE style)
{
	// Lazy init
	if(_instance == NULL)
	{
		_instance = new Deck(style);
	}
	
	assert(_instance != NULL);
	
	if(_instance->style() != style)
	{
		//Current deck of cards is not the type requested
		std::cout << "Request a new deck of cards when current is in use.\n";
		std::cout << "Current style of cards: " << _instance->style() << "\n";
		std::cout << "Request style of cards: " << style << "\n";
		return NULL;
	}
	
	return _instance;
}

CARD_STYLE Deck::style()
{
	return _style;
}

void Deck::destroy()
{
	if(_instance != NULL)
	{
		delete _instance;
		_instance = NULL;
	}
}

// Initialize 52 cards with rank from 1 to 13 and 
// suits of hearts, spades, clubs, diamonds
// Todo: Exception handling
bool Deck::initialize()
{
	// Get corresponsding card factory to card type
	CardFactory* factory = NULL;
	switch(_style)
	{
		case DEFAULT_CARD_STYLE:
		{
			factory = DefaultCardFactory::instance();
		}
		break;
		case FRANCE_CARD_STYLE:
		{
			//factory = FranceCardFactory::instance();
		}
		break;
		case GERMAN_CARD_STYLE:
		{
			//factory = GermanCardFactory::instance();
		}
		break;
		default:
		{
			factory = DefaultCardFactory::instance();
		}
	}
	
	if(factory == NULL)
	{
		return false;
	}
	
	// Create cards with current card factory
	for(int i=0; i<13; ++i)
	{
		// * We did not use loop on the value of SUIT here
		//   to remove the dependence of their predefined values
		_cards.push_back(factory->create(i+1, Card::HEART));
		_cards.push_back(factory->create(i+1, Card::SPADE));
		_cards.push_back(factory->create(i+1, Card::CLUB));
		_cards.push_back(factory->create(i+1, Card::DIAMOND));
		
		// Otherwise
		//for(int j=0; j<4; ++j)
		//{
		//	_cards.push_back(factory->create(i+1, j));
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
	for(int i=n-1; i>=0; --i)
	{
		std::swap(_cards[i], _cards[rand() % (i+1)]); // Random range [0, i]
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
