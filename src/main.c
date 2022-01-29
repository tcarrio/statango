#ifndef TIMER_SECONDS
#define TIMER_SECONDS 1
#endif

#include <unistd.h>

#include "battery.c"
#include "date.c"

static const int timer_seconds = TIMER_SECONDS;

int main(void) {
    while (1) {
        fprintf(stdout, "%s | %s", get_date(), get_battery());
        sleep(timer_seconds);
    }

    return 0;
}
