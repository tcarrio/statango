#include "battery.c"
#include "date.c"

int main(void) {
    fprintf(stdout, "%s | %s", get_date(), get_battery());

    return 0;
}
