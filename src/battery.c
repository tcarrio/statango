#ifdef PLATFORM_LINUX
#define BATTERY_FILE "/sys/class/power_supply/BAT0/capacity"
#else
#define BATTERY_FILE "/dev/null"
#error Only Linux is supported
#endif /* PLATFORM_LINUX */

#include <stdio.h>

static char* BATTERY_0 = u8"\uf244";
static char* BATTERY_25 = u8"\uf243";
static char* BATTERY_50 = u8"\uf242";
static char* BATTERY_75 = u8"\uf241";
static char* BATTERY_100 = u8"\uf240";

char* get_battery_icon(int value) {
    if (value < 25) {
        return BATTERY_0;
    }

    if (value < 50) {
        return BATTERY_25;
    }

    if (value < 75) {
        return BATTERY_50;
    }

    if (value < 100) {
        return BATTERY_75;
    }

    return BATTERY_100;
}

char* get_battery() {
    static char battery_level[12];

    char battery[4];
    FILE *battery_f = fopen(BATTERY_FILE, "r");
    fgets(battery, sizeof(battery), battery_f);

    int battery_value;
    sscanf(battery, "%d", &battery_value);

    char* battery_icon = get_battery_icon(battery_value);

    sprintf(battery_level, "%s %d%%", battery_icon, battery_value);

    fclose(battery_f);

    return battery_level;
}
