#include "timedata.h"
#include <time.h>

static TimeData global_time = { 0 };

static double nsectosec(long nsec);
static double timespectosec(struct timespec ts);

void time_start(void) {
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  global_time.time_start = timespectosec(ts);
  global_time.time_now = global_time.time_start;
  global_time.delta_time = 0.0;
  global_time.time_elapsed = 0.0;
}

void time_stamp(void) {
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  double newTime = timespectosec(ts);
  global_time.time_elapsed = newTime - global_time.time_start;
  global_time.delta_time = newTime - global_time.time_now;
  global_time.time_now = newTime;
}

TimeData time_get(void) {
  return global_time;
}

static double nsectosec(long nsec) {
  double seconds = 1.0 * nsec;
  return seconds / 1000000000;
}

static double timespectosec(struct timespec ts) {
  double seconds = (double)ts.tv_sec;
  seconds += nsectosec(ts.tv_nsec);
  return seconds;
}

