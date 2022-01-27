#ifdef PLATFORM_LINUX
#define BATTERY_FILE "/sys/class/power_supply/BAT0/capacity"
#else
#error Only Linux is supported
#endif /* PLATFORM_LINUX */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

char* get_date() {
    static char date_str[40];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return date_str;
}

char* get_battery() {
    static char battery_level[4];

    char battery[3];
    FILE *battery_f = fopen(BATTERY_FILE, "r");

    fgets(battery, sizeof(battery), battery_f);
    sprintf(battery_level, "%s%%", battery);

    fclose(battery_f);

    return battery_level;
}

int main(void) {
    char output[80];

    fprintf(stdout, "%s | %s", get_date(), get_battery());

    return 0;
}
