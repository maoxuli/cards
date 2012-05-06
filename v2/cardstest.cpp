//
// This is a solution of classic Deck of Cards problem. 
// V2
//
// Author: Maoxu Li
// Date: Apr 14, 2012
// Email: li@maoxuli.com
//

#ifndef __CARDS_TEST_H
#define __CARDS_TEST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "cards.h"

//
// Timer for performance measure
// High precision timer over platforms of
// Windows, Mac OS X, and Linux
// Usage:
// 1. time_start() to start timing
// 2. time_elapse() to return time in microseconds (us) from time_start()
//

// For Windows
#ifdef _WIN32 
#include <windows.h>

LARGE_INTEGER timerFreq;
LARGE_INTEGER startCounter;

// Start to timing
void time_start()
{
  QueryPerformanceFrequency(&timerFreq);
  QueryPerformanceCounter(&startCounter);
}

// Time elapse from time_start
// Return microseconds (us)
int time_elapse()
{
  if (timerFreq.QuadPart == 0)
  {
    return -1;
  }
  else
  {
    LARGE_INTEGER stopCounter;
    QueryPerformanceCounter(&stopCounter);
    return static_cast<int>((stopCounter.QuadPart - startCounter.QuadPart) * 1000000 / timerFreq.QuadPart);
  }
}

// For Mac OS X and Linux
#else
#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

timespec startTimer;

// Get current time of system in nanoseconds from ...
void sys_gettime(struct timespec* ts)
{	
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_REALTIME, ts);
#endif
}

// Start timing
void time_start()
{
	sys_gettime(&startTimer);
}

// Time elapse from time_start
// Return microseconds (us)
int time_elapse()
{
	timespec stopTimer;
	sys_gettime(&stopTimer);
	
	return (stopTimer.tv_sec * 1000000 + stopTimer.tv_nsec / 1000) 
		  	- (startTimer.tv_sec * 1000000 + startTimer.tv_nsec/1000);
}

#endif 

//
// Display deck of cards in order based on dealing cards operations
// This function works depend on current iterator of the deck of cards
// In general, it works only immediately after a instance of Deck is
// initiated or shuffled.
// In addition, once a deck of cards is displayed, it can not be 
// dealted until shuffled again.
//
void display(Deck* deck)
{
	std::cout << "Deck of cards ( rank [suit] ):\n";
	Card* card = deck->deal_one_card();
	int i = 1;
	while(card != NULL)
	{		
		std::cout << std::setw(2) << std::setiosflags(std::ios::right) << card->rank() 
		<< std::setw(3) << std::setiosflags(std::ios::left) << "[" << card->suit() << "]"
		<< (i++ % 4 == 0 ? "\n" : "\t\t");
		card = deck->deal_one_card();
	}
	std::cout << "\n";
}

//
// This is a testing process for Deck of Cards implementation.
// The testing focused on shuffle algorithm.
// Interactive with users to determine the rounds of shuffle.
// Shuffle algorithm is measured in terms of running time.
//

int main(int argc, const char* argv[])
{
	std::cout << "\nThis is a testing of Deck of Cards.\n"
				 "Author: Maoxu Li, li@maoxuli.com\n";
	
	std::cout << "\nInitialize a deck of cards...\n";

	// Test with a new Deck
	Deck* deck = Deck::instance(DEFAULT_CARD_STYLE);
	assert(deck != NULL);
	display(deck);
			
	std::cout << "\nTesting of shuffle with different shuffle rounds.\n";
	
	while(true)
	{
		std::cout << "\nPlease input a number of shuffle rounds (input 0 to exit): ";
		int rounds = 0;
		std::cin >> rounds;

		if(rounds == 0)
		{
			break;
		}
		
		// Shuffle
		std::cout << "\nShuffle rounds: " << rounds << "...\n";
		time_start();
		
		for(int i=0; i<rounds; ++i)
		{
			deck->shuffle();
		}
		
		int t = time_elapse();
		std::cout << "Shuffled with " << t << " microseconds (us).\n";
		display(deck);
	}
	
	std::cout << "\nDestroy the deck of cards...\n";
	deck->destroy();
	deck = NULL;
	
	std::cout << "\nTest is over!\n\n";
	return 0;
}

#endif
