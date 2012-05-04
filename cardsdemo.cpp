//
// This is a solution of classic Deck of Cards problem. 
//
// Author: Maoxu Li
// Date: Apr 14, 2012
// Email: li@maoxuli.com
//

#ifndef __CARDS_TEST_H
#define __CARDS_TEST_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "cards.h"

int main(int argc, const char* argv[])
{
	std::cout << "\nThis a demonstration of Deck of Cards.\n"
				 "Author: Maoxu Li, li@maoxuli.com\n\n";
	
	// Game start with a new deck of cards
	std::cout << "Game start...\n\n";
	Deck* deck = new Deck();
	assert(deck != NULL);
	
	// Shuffle
	std::cout << "Shuffle...\n";
	deck->shuffle();
	std::cout << "shuffled.\n\n";
						
	// Deal cards
	std::cout << "Deal cards:\n";
	Card* card = deck->deal_one_card();
	int i = 1;
	while(card != NULL)
	{		
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << card->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "(" << card->suit() << ")"
		<< (i++ % 4 == 0 ? "\n" : "\t\t");
		card = deck->deal_one_card();
	}
	std::cout << std::endl;
	
	// Game over, clear
	delete deck;
	deck = NULL;
	std::cout << "Game over!\n\n";
	
	getchar();
	return 0;
}

#endif
