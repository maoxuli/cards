//
// This is a solution of classic Desk of Cards problem. 
// V2
//
// Author: Maoxu Li
// Date: May 5, 2012
// Email: li@maoxuli.com
//

#ifndef __CARDS_H
#define __CARDS_H

#include <vector>

//
// A card is one entity of a deck of cards.
// It is identified with rank (1~13) and 
// suit (heart, spade, club, diamond).
//

// Card is defined as interface of concrete card class 
// Abstract class
class Card 
{
public:
	enum SUIT { HEART = 0, SPADE, CLUB, DIAMOND };
	
	// return rank
	virtual int rank() = 0; 
	
	// return suit
	virtual SUIT suit() = 0;
	
	// Draw card on screen
	// Different types of cards has different implmentations
	virtual void draw() = 0;	
};

// A concrete card class is initiated with corresponding factory
// CardFactory is defined as interface of concrete card factory
// Abstract class
class CardFactory
{
public:
	virtual Card* create(int rank, Card::SUIT suit) = 0;
};

// Type of concrete cards
// They have different suit design
enum CARD_TYPE { DEFAULT_CARD_TYPE = 0, FRANCE_CARD_TYPE, GERMAN_CARD_TYPE };

// Concrete card factory class for default card type
// Singleton Pattern
// Internal release, no outer release interface
class DefaultCardFactory : public CardFactory
{
public:
	virtual ~DefaultCardFactory();
	static DefaultCardFactory* instance();
	
	virtual Card* create(int rank, Card::SUIT suit);
	
private:
	DefaultCardFactory();
	static DefaultCardFactory* _instance;
	
	// Helper class to delete singleton instance
    class Deleter
    {
    public:
        Deleter() {};
        ~Deleter()
        {
            if(DefaultCardFactory::_instance != NULL)
            {
                delete DefaultCardFactory::_instance;
				DefaultCardFactory::_instance = NULL;
            }
        }
    };
    friend class Deleter;
    static Deleter _deleter;
};

// Concrete card class for default card type 
// Default implementation of card
class DefaultCard : public Card
{
public:
	virtual ~DefaultCard();
	
	// return rank
	virtual int rank(); 
	
	// return suit
	virtual SUIT suit();
	
	// Draw card on screen
	virtual void draw();
	
private:
	DefaultCard(); // no implementation
	DefaultCard(int rank, SUIT suit);
	friend class DefaultCardFactory;
	
	int _rank;
	SUIT _suit;	
};

//
// A deck of cards consists of a certian number cards (52 in this case). 
// Shuffle and deal one card is implemented here.
//

// Singleton Pattern
// with outer release interface
// Must be released by caller before application exit
class Deck 
{
public:
	virtual ~Deck();
	static Deck* instance(CARD_TYPE type = DEFAULT_CARD_TYPE);
	
	CARD_TYPE type();
	void destroy();
	
	void shuffle();
	Card* deal_one_card();
	
private:
	Deck(); // No implementation
	Deck(CARD_TYPE type);
	static Deck* _instance;
	
	// Internal operation to initialize deck of cards
	bool initialize();
	CARD_TYPE _type;
	
	// Deck of cards
	typedef std::vector<Card*> CardSeq;
	CardSeq _cards;
	
	// Iterator for deal cards
	// Advance with deal cards operation
	// Reset with shuffle operation
	// Using iterator is safe here only because 
	// card is not move or removed in this design.
	// (Using index otherwise) 
	CardSeq::const_iterator _iterator;
};

#endif
