#ifdef __linux__
#define BATTERY_CHARGE_FILE "/sys/class/power_supply/BAT0/capacity"
#define BATTERY_STATUS_FILE "/sys/class/power_supply/BAT0/status"
#else
#define BATTERY_CHARGE_FILE "/dev/null"
#define BATTERY_STATUS_FILE "/dev/null"
#error Only Linux is supported
#endif

#define BATTERY_STATUS_DISCHARGING_LENGTH 12

#include <stdio.h>
#include <string.h>


/**
 * The file contents of the battery status file when charging
 */
static char BATTERY_STATUS_DISCHARGING[BATTERY_STATUS_DISCHARGING_LENGTH] = "Discharging";

/**
 * Battery icons
 */
static char* ICON_CHARGING = u8"\uf1e6";
static char* ICON_BATTERY_0 = u8"\uf244";
static char* ICON_BATTERY_25 = u8"\uf243";
static char* ICON_BATTERY_50 = u8"\uf242";
static char* ICON_BATTERY_75 = u8"\uf241";
static char* ICON_BATTERY_100 = u8"\uf240";

char* get_battery_icon(int value, int is_charging) {
    if (is_charging) {
        return ICON_CHARGING;
    }

    if (value < 25) {
        return ICON_BATTERY_0;
    }

    if (value < 50) {
        return ICON_BATTERY_25;
    }

    if (value < 75) {
        return ICON_BATTERY_50;
    }

    if (value < 100) {
        return ICON_BATTERY_75;
    }

    return ICON_BATTERY_100;
}

void get_is_charging(int *is_charging) {
    char battery_status[BATTERY_STATUS_DISCHARGING_LENGTH];
    FILE *battery_status_f = fopen(BATTERY_STATUS_FILE, "r");
    fgets(battery_status, sizeof(battery_status), battery_status_f);

    fprintf(stderr, "battery status: %s\n", battery_status);

    *is_charging = strcmp(battery_status, BATTERY_STATUS_DISCHARGING) != 0;

    fclose(battery_status_f);
}

void get_battery_value(int *battery_value) {
    char battery[4];
    FILE *battery_charge_f = fopen(BATTERY_CHARGE_FILE, "r");
    fgets(battery, sizeof(battery), battery_charge_f);

    sscanf(battery, "%d", battery_value);

    fclose(battery_charge_f);
}

char* get_battery() {
    static char battery_level[12];

    int is_charging;
    get_is_charging(&is_charging);

    int battery_value;
    get_battery_value(&battery_value);

    char* battery_icon = get_battery_icon(battery_value, is_charging);

    sprintf(battery_level, "%s %d%%", battery_icon, battery_value);

    return battery_level;
}
