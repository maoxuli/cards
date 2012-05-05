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
// Timer for performance measure
//
#ifdef _WIN32
#include <windows.h>

LARGE_INTEGER timerFreq;
LARGE_INTEGER startCounter;

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


#else
#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

// System time
void get_time(struct timespec *ts)
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

// Time interval
timespec diff(timespec &start, timespec &end)
{
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) 
	{
         temp.tv_sec = end.tv_sec - start.tv_sec - 1;
         temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } 
	else  
	{
         temp.tv_sec = end.tv_sec - start.tv_sec;
         temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

#endif 

int main(int argc, const char* argv[])
{
	std::cout << "\nThis a testing of Deck of Cards.\n"
				 "Author: Maoxu Li, li@maoxuli.com\n\n";
	
	// Test shuffle with different shuffle rounds
	std::cout << "Test shuffle with different shuffle rounds.\n";
	
	int rounds = 0;
	while(true)
	{
		std::cout << "Please input a number of shuffle rounds (input 0 to exit): ";
		std::cin >> rounds;

		if(rounds == 0)
		{
			break;
		}
		
		std::cout << "\nNew deck of cards for testing...\n";
	
		// Test with a new Deck
		Deck* deck = new Deck(rounds);
		assert(deck != NULL);
		deck->dump();
	
		// Shuffle
		std::cout << "\nShuffle rounds: " << rounds << "...\n";
		//timespec time1, time2;
		//get_time(&time1);
		time_start();
		deck->shuffle();
		int t = time_elapse();
		std::cout << "Shuffled with " << t << " microseconds (us).\n\n";
		deck->dump();
	
		// Clear deck
		delete deck;
		deck = NULL;
		std::cout << "Deck is clear and destroyed!\n\n";
	}
	
	std::cout << "Test is over!\n\n";
	getchar();
	return 0;
}

#endif
