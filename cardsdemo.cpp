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

//
// This is a demo process for Deck of Cards implementation
// It simulates below processes:
// 1. Initialize a deck of cards
// 2. Shuffle
// 3. Deal one card each time until finished all
// 4. Shuffle cards to reset
// 5. Deal a part of cards
// 6. Shuffle cards multiple times
// 7. Deal all cards
// 8. Destroy the deck of cards
//

int main(int argc, const char* argv[])
{
	std::cout << "\nThis a demonstration of Deck of Cards.\n"
				 "Author: Maoxu Li, li@maoxuli.com\n";
	
	std::cout << "\nGame start...\n";
	
	// Initialize a deck of cards
	std::cout << "\n1. Initialize a deck of cards...\n";
	Deck* deck = new Deck();
	assert(deck != NULL);
	
	// Shuffle
	std::cout << "\n2. Shuffle cards...\n";
	deck->shuffle();
						
	// Deal cards
	std::cout << "\n3. Deal cards...\n";
	Card* card = deck->deal_one_card();
	int i = 1;
	while(card != NULL)
	{		
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << card->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "(" << card->suit() << ")"
		<< (i++ % 4 == 0 ? "\n" : "\t\t");
		card = deck->deal_one_card();
	}
	std::cout << "\n";
	
	// Shuffle
	std::cout << "\n4. Shuffle cards...\n";
	deck->shuffle();
						
	// Deal cards
	std::cout << "\n5. Deal cards...\n";
	card = deck->deal_one_card();
	i = 1;
	while(card != NULL && i < 25)
	{		
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << card->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "(" << card->suit() << ")"
		<< (i++ % 4 == 0 ? "\n" : "\t\t");
		card = deck->deal_one_card();
	}
	std::cout << "\n";
	
	// Shuffle
	std::cout << "\n6. Shuffle cards...\n";
	deck->shuffle();
	deck->shuffle();
						
	// Deal cards
	std::cout << "\n7. Deal cards...\n";
	card = deck->deal_one_card();
	i = 1;
	while(card != NULL)
	{		
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << card->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "(" << card->suit() << ")"
		<< (i++ % 4 == 0 ? "\n" : "\t\t");
		card = deck->deal_one_card();
	}
	std::cout << "\n";
	
	// Game over, clear
	std::cout << "\n8. Destroy the deck of cards...\n";
	delete deck;
	deck = NULL;
	
	std::cout << "\nGame over!\n\n";
	std::cin.get();
	return 0;
}

#endif
