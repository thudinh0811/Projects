#ifndef _TIME_DATA_H
#define _TIME_DATA_H

struct TimeData {
  double time_start;
  double delta_time;
  double time_elapsed;
  double time_now;
};
typedef struct TimeData TimeData;

void time_start(void);
void time_stamp(void);
TimeData time_get(void);

#endif /* _TIME_DATA_H */
