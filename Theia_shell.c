#include <stdio.h>
#include <string.h>
#include "theia_log.h"
#include "theia_bridge.h" 

void theia_shell_loop() {
    char input[256];
    printf("Theia [Forbidden Mode] v0.1 initialized. Type 'help' for commands.\n");

    while (1) {
        printf("theia> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) break;

        if (strcmp(input, "swift") == 0) {
            THEIA_LOG(LOG_INFO, "Switching control to Swift Runtime...");
            theia_overlord_execute(1, NULL);
        } else if (strcmp(input, "holyc") == 0) {
            THEIA_LOG(LOG_INFO, "Switching control to HolyC Soul...");
            theia_overlord_execute(0, NULL);
        } else {
            printf("Unknown command: %s. Theia is watching.\n", input);
        }
    }
}
