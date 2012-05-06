//
// This is a solution of classic Desk of Cards problem. 
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

// Card is defined as a abstract class 
// A interface for Card
class Card 
{
public:
	enum SUIT { HEART = 0, SPADE, CLUB, DIAMOND };
	
	// return rank
	virtual int rank() = 0; 
	
	// return suit
	virtual SUIT suit() = 0;
	
	// Draw card on screen
	virtual void draw() = 0;	
};

// Card is iniatated with a card factory
// A interface for Card Factory
class CardFactory
{
public:
	virtual Card* create(int rank, Card::SUIT suit) = 0;
};

// Type of concrete deck of cards
enum CARD_TYPE { DEFAULT_CARD_TYPE = 0, FRANCE_CARD_TYPE, GERMAN_CARD_TYPE };

// Concrete card class for default card type 
// Default implementation of card
class DefaultCard : public Card
{
public:
	DefaultCard();
	DefaultCard(int rank, SUIT suit);
	virtual ~DefaultCard();
	
	// A card may be set explicitly 
	// (or implicitly with constructor otherwise)
	void set(int rank, SUIT suit);
	
	// return rank
	virtual int rank(); 
	
	// return suit
	virtual SUIT suit();
	
	// Draw card on screen
	virtual void draw();
	
protected:
	int _rank;
	SUIT _suit;	
};

//
// A factory to initiate default type card
// Singleton pattern
//
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

//
// A deck of cards consists of a certian number of 
// deiffernt cards (52 in this case). 
// Shuffle and deal one card is implemented here.
// Deck class is in a singleton pattern with destroy 
// operation to create new singleton
//
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
	Deck();
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
