/*
 * Time.h
 *
 * This header file defines some commonly used time support functions.
 *
 * This file is subject to the terms and conditions defined in
 * file 'COPYRIGHT.txt', which is part of this source code package.
 */

#ifndef TIME_H_
#define TIME_H_

#include <sys/time.h>

// We define TIME as a double. This provides enough resolution to describe with some accuracy
// plus it makes it fairly straightforward to work in times time based math.
typedef double TIME;

// The GetTime function is grabs the amount of time since Epoch offering a point of reference
// for comparison.
TIME GetTime();

// The CompareTime function compares time a and time b. If b minus a is less then ms, the
// function returns true, otherwise false.
bool CompareTime(TIME* a, TIME* b, int ms);

// The timeval2timespec and timespecAdd functions are support functions specifically used by
// the Thread class for determining the length of time to sleep for.
timespec* timeval2timespec(timespec* dest, timeval* source);
timespec* timespecAdd(timespec* ts, int ms);

#endif /*TIME_H_*/

