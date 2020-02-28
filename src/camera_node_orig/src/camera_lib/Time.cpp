/*
 * Time.cpp
 *
 * This file provides the implementation of commonly used time support functions.
 *
 * This file is subject to the terms and conditions defined in
 * file 'COPYRIGHT.txt', which is part of this source code package.
 */

#include "Time.h"
// #include <vision_opencv>

// The GetTime function is grabs the amount of time since Epoch offering a point of reference
// for comparison.
TIME GetTime()
{
    timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + (t.tv_usec / 1000000.0);
}

// The CompareTime function compares time a and time b. If b minus a is less then ms, the
// function returns true, otherwise false.
bool CompareTime(TIME* a, TIME* b, int ms)
{
    return (*b - *a < ms / 1000.0);
}

// The timeval2timespec and timespecAdd functions are support functions specifically used by
// the Thread class for determining the length of time to sleep for.
timespec* timeval2timespec(timespec* dest, timeval* source)
{
    dest->tv_sec = source->tv_sec;
    dest->tv_nsec = (source->tv_usec * 1000);
    return dest;
}
timespec* timespecAdd(timespec* ts, int milliseconds)
{
    ts->tv_sec += (milliseconds / 1000);
    ts->tv_nsec += ((long)((milliseconds % 1000) * 1000000));

    /* Should we carry the result? */
    if (ts->tv_nsec >= 1000000000L)
    {
        ts->tv_sec++;
        ts->tv_nsec -= 1000000000L;
    }

    return ts;
}
