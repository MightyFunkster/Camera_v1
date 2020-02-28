/*
 * Thread.cpp
 * 
 * This class is used to provide object level threading support. It defines
 * a class with a single thread which initialises and calls the Execute
 * method as it loops. It provides the ability to sleep, wait and be
 * signalled. It is based on Posix threads.
 * 
 * This file is subject to the terms and conditions defined in
 * file 'COPYRIGHT.txt', which is part of this source code package.
 */

#include "Thread.h"
// #include <vision_opencv>

// The Thread classes constructor which sets up our initial state.
Thread::Thread()
{
    // Set up our local variables which defines our inactive state.
    threadID = 0;
    active = false;
    abort = false;

    // Initialise our mutex and condition.
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
}

// The Thread classes destructor which performs the clean up.
Thread::~Thread()
{
    // Make sure the thread is stopped. If it isn't wait here until the thread is
    // correctly disposed of.
    Stop(true);

    // Destroy our mutex and condition.
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

// The static EntryPoint method is used by the Posix thread as an entry point on
// start up. We use the argument to pass to the new thread a reference to its
// related Thread object so that it can invoke the objects Run method to perform
// the main threading functionality.
void* Thread::EntryPoint(void* arg)
{
    ((Thread*)arg)->Run();
    return 0;
}

// The IsAlive method returns our local variables flag on whether the thread is
// currently active.
bool Thread::IsAlive()
{
    return active;
}

// The Start method calls the Posix thread creation function to construct us a
// new thread and get things started.
bool Thread::Start()
{
    if(pthread_create(&threadID, NULL, Thread::EntryPoint, this) != 0)
    {
        printf("failed to create thread");
        return false;
    }

    return true;
}

// The WaitForExit method causes the calling thread to wait for this thread to
// exit. The caller should never be this thread.
void Thread::WaitForExit()
{
    pthread_join(threadID, NULL);
}

// The Stop method calls the overloaded Stop method instructed it not to wait for
// the thread to exit.
bool Thread::Stop()
{
    return Stop(false);
}

// The Stop method sets the abort flag and wakes up the thread (in case it is
// in a sleep state). The abort flag will cause the Run method to exit its loop. If
// the wait argument is true, the Stop method will not exit until the thread has
// finished.
bool Thread::Stop(bool wait)
{
    if(active)
    {
        abort = true;
        Signal();

        if(wait) WaitForExit();
    }

    return true;
}

// The Initialise method defines default behaviour in case it isn't overridden by
// an inheriting class.
bool Thread::Initialise()
{
    return true;
}

// The Run method is the first real starting point (after the EntryPoint) for a newly
// constructed thread. Effectively it calls Initialise and if that all goes to plan
// then enters a continuous loop calling the Execute method.
bool Thread::Run()
{
    bool result = false;
    if(Initialise())
    {
        result = true;
        abort = false;
        active = true;
        while(!abort)
        {
            gettimeofday(&startTime, 0);
            if(!Execute()) break;
        }
        active = false;	
    }
    pthread_exit(0);	
    return result;
}

// The Execute method defines default behaviour in case it isn't overridden by an
// inheriting class.
bool Thread::Execute()
{
    return true;
}

// The InternalSleep method is a private method designed to perform the job of
// sleeping in a thread safe manor.
void Thread::InternalSleep(timespec* req)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_timedwait(&cond, &mutex, req);
    pthread_mutex_unlock(&mutex);
}

// The Sleep method causes the thread to sleep for the required number of
// milliseconds.
void Thread::Sleep(int ms)
{
    timeval t;
    gettimeofday(&t, 0);

    timespec req;
    timespecAdd(timeval2timespec(&req, &t), ms);

    InternalSleep(&req);
}

// The Sleep method causes the thread to sleep for the required number of
// milliseconds minus the amount of time required to complete the last
// Execute method iteration.
void Thread::SleepTo(int ms)
{
    timespec req;
    timespecAdd(timeval2timespec(&req, &startTime), ms);

    InternalSleep(&req);
}

// The Wait method puts the thread in a permanent sleep state until it
// is woken up again.
void Thread::Wait()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

// The Signal method brings the thread out of a sleeping or waiting
// state.
void Thread::Signal()
{
    pthread_cond_signal(&cond);
}