#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int tty_num = ttyslot();

    if (tty_num > 0) {
        char* tty_name = ttyname(tty_num);
        if (tty_name) {
            printf("Terminal device: %s\n", tty_name);
        } else {
            printf("Error: cannot determine terminal device name.\n");
        }
    } else {
        printf("Error: process is not associated with a terminal device.\n");
    }

    return 0;
}
