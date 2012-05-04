//
// This is a solution of classic Desk of Cards problem. 
//
// Author: Maoxu Li
// Date: Apr 14, 2012
// Email: li@maoxuli.com
//

#ifndef __CARDS_H
#define __CARDS_H

#include <vector>

enum SUIT { HEART, SPADE, CLUB, DIAMOND };

class Card 
{
public:
	Card(int rank, SUIT suit);
	virtual ~Card();
	
	int rank(); 
	SUIT suit();	
	
private:
	int _rank;
	SUIT _suit;
};

class Deck 
{
public:
	// Shuffle rounds, 0 for default rounds
	Deck(int rounds = 0);
	virtual ~Deck();
	
	void shuffle();
	Card* deal_one_card();
	
	// For testing purpose only
	// display all cards in screen
	void dump();
	
private:
	typedef std::vector<Card*> CardSeq;
	CardSeq _cards;
	
	int _shuffle_rounds; 
	
	 // Iterator for deal cards
	CardSeq::const_iterator _iterator;
};

#endif
