#ifndef PROFILE_H
#define PROFILE_H

#define PROFILE_BEGIN() profiler_start_counter(__FUNCTION__)
#define PROFILE_END() profiler_stop_counter(__FUNCTION__)

void profiler_reset_counters(void);
void profiler_start_counter(const char* key);
void profiler_stop_counter(const char* key);
void profiler_update_counters();

#endif
