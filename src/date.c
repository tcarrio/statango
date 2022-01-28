#include <stdio.h>
#include <time.h>

char* get_date() {
    static char date_str[40];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str,
            "%d-%02d-%02d %02d:%02d:%02d",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    return date_str;
}
