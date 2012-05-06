//
// This is a solution of classic Desk of Cards problem. 
//
// Author: Maoxu Li
// Date: May 4, 2012
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
class Card 
{
public:
	enum SUIT { HEART = 0, SPADE, CLUB, DIAMOND };
	
	Card();
	Card(int rank, SUIT suit);
	virtual ~Card();

	// A card can be set explicitly
	// (or implicitly with constructor otherwise)
	void set(int rank, SUIT suit);
	
	// return rank
	int rank(); 
	
	// return suit
	SUIT suit();	
	
private:
	int _rank;
	SUIT _suit;
};

//
// A deck of cards consists of a certian number of 
// deiffernt cards (52 in this case). 
// Shuffle and deal one card is implemented here.
//
class Deck 
{
public:
	Deck();
	virtual ~Deck();
	
	void shuffle();
	Card* deal_one_card();
	
private:
	// Internal operation to initialize deck of cards
	bool initialize();
	
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
