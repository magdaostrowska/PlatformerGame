#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

#include "Source/Defs.h"

class PerfTimer
{
public:

	// Constructor
	PerfTimer();
	// Destructor
	~PerfTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;

private:
	uint64 startTime;
	static uint64 frequency;
};

#endif //__PERFTIMER_H__