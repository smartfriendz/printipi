#ifndef COMMON_TIMEUTIL_H
#define COMMON_TIMEUTIL_H

/* 
 * Printipi/timeutil.h
 * (c) 2014 Colin Wallace
 *
 * This file provides convenience functions for dealing with Linux high-resolution timers.
 */

#include <time.h>
#include <chrono>

timespec timespecNow();
timespec timespecAdd(const struct timespec &a, const struct timespec &b);
timespec timespecSub(const struct timespec &a, const struct timespec &b);
const timespec& timespecMin(const struct timespec &a, const struct timespec &b);
//return -1 for a < b, 0 for a == b, 1 for a > b
int timespecCmp(const struct timespec &a, const struct timespec &b);
bool timespecLt(const struct timespec &a, const struct timespec &b);
inline bool timespecLte(const struct timespec &a, const struct timespec &b) {
	//if not b < a,
	//then b >= a
	//so a <= b
	return !timespecLt(b, a);
}
inline bool timespecGt(const struct timespec &a, const struct timespec &b) {
	//if not a <= b,
	//then a > b
	return !timespecLte(a, b);
}
float timespecToFloat(const struct timespec &a);
timespec floatToTimespec(float f);
template <typename T> timespec durationToTimespec(const T& abs) {
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(abs);
	auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(abs)-sec;
	return timespec{(time_t)sec.count(), (long int)nsec.count()};
}
template <typename T> timespec timepointToTimespec(const T& timepoint) {
	auto abs = timepoint.time_since_epoch(); //clock's epoch, not 1970.
	return durationToTimespec(abs);
}
inline std::chrono::nanoseconds timespecToDuration(const timespec &ts) {
	return std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec);
}
template <typename T> T timespecToTimepoint(const timespec &ts) {
	auto asDuration = timespecToDuration(ts);
	return T(asDuration);
}

#endif
