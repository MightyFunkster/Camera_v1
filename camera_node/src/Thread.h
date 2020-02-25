/*
 * File:    Thread.h
 * Author:  Dr.Anthony Portelli
 * 
 * This is a header file for Thread.cpp
 * 
 * This file is subject to the terms and conditions defined in
 * file 'COPYRIGHT.txt', which is part of this source code package.
 */

#ifndef THREADED_H_
#define THREADED_H_

// *****************************************************************************
// * Include Files
// *****************************************************************************
#include <pthread.h>
#include <stdio.h>
#include "Time.h"

class Thread
{
private:
	// The threadID variable store reference to our Posix thread.
	pthread_t threadID;
	
	// The mutex and cond variables provide us with a mutex and
	// condition to be used in scenarios such as Wait and sleeping
	// for a given period.
	pthread_mutex_t mutex;	
	pthread_cond_t cond;
	
	// Define some private variables to help manage the threads state.
	bool abort;
	bool active;

protected:
	// The startTime variable is used to get the start time of a given
	// iteration around the threads loop.
	timeval startTime;

private:
	// The InternalSleep method is used perform the timed sleep used
	// the thread condition support functions.
	void InternalSleep(timespec* req);
	
	// The static EntryPoint method is the point at which the new Posix
	// thread starts.
	static void* EntryPoint(void* arg);
	
protected:
	// The Sleep method is used to put the thread to sleep for a given
	// number of milliseconds.
	void Sleep(int ms);
	
	// The SleepTo method is used to put the thread to sleep for a given
	// number of milliseconds minus the amount of time that the thread
	// has been processing this iteration round the threads loop (the amount
	// of time it has taken to perform the last Execute).
	void SleepTo(int ms);
	
	// The Wait method puts the thread to sleep until is is woken up by
	// a call to Signal but another thread.
	void Wait();
	
	// The Signal method wakes up a sleeping or waiting thread.
	void Signal();
	
public:
	// The thread classes constructor and destructor.
	Thread();
	virtual ~Thread();

	// The WaitForExit method can be called to force the calling thread to
	// wait for this thread to exit before completing.
	void WaitForExit();

	// The Run method is the main processing method called following the threads
	// creation. The default behaviour, if it is not overridden is to called
	// Initialise then enter a continuous loop calling Execute through each
	// iteration.
	virtual bool Run();
	
	// The Initialise method is a method designed to be overridden by a derived
	// class to offer initialisation support prior to the thread starting its
	// main loop.
	virtual bool Initialise();
	
	// The Execute method is called continuously as the thread is running.
	virtual bool Execute();

	// The IsAlive method reports back to indicate whether the thread is currently
	// alive and running.
	bool IsAlive();
	
	// The IsAbort method reports back whether an abort request has been been
	// made.
	bool IsAbort() { return abort; };
	
	// The Start method creates a new thread and gets it running.
	bool Start();
	
	// The Stop method causes the thread to gracefully shutdown. The overloaded
	// version includes an argument to indicate whether to wait for completion
	// before returning.
	bool Stop();
	bool Stop(bool wait);
};

#endif /*THREADED_H_*/
