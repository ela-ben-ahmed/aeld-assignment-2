#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Expected 2 arguments, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <file_path> <string_to_write>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Failed to open file %s for writing: %s", writefile, strerror(errno));
        perror("Error opening file");
        closelog();
        return 1;
    }

    if (fputs(writestr, file) == EOF) {
        syslog(LOG_ERR, "Error: Failed to write string to file %s: %s", writefile, strerror(errno));
        perror("Error writing to file");
        fclose(file);
        closelog();
        return 1;
    }

    fclose(file);
    closelog();
    return 0;
}
