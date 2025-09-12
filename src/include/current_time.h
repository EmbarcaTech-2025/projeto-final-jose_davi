#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

extern void setup_rtc_from_ntp();
extern void get_current_timestamp_str(char* buf, size_t len);

#endif 