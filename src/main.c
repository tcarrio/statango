#ifndef TIMER_SECONDS
#define TIMER_SECONDS 1
#endif

#include <unistd.h>

#include "battery.c"
#include "date.c"

int main(void) {
    while (1) {
        fprintf(stdout, "%s | %s", get_date(), get_battery());
        fflush(stdout);
        sleep(1);
        fprintf(stdout, "\n");
    }

    return 0;
}
