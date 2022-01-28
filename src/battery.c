#ifdef PLATFORM_LINUX
#define BATTERY_FILE "/sys/class/power_supply/BAT0/capacity"
#else
#define BATTERY_FILE "/dev/null"
#error Only Linux is supported
#endif /* PLATFORM_LINUX */

#include <stdio.h>


char* get_battery() {
    static char battery_level[5];

    char battery[4];
    FILE *battery_f = fopen(BATTERY_FILE, "r");
    fgets(battery, sizeof(battery), battery_f);

    int battery_value;
    sscanf(battery, "%d", &battery_value);

    sprintf(battery_level, "%d%%", battery_value);

    fclose(battery_f);

    return battery_level;
}
