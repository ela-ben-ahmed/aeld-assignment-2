#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    
    openlog("writer", LOG_PID, LOG_USER);

    
    if (argc < 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Usage: %s <string> <file>", argv[0]);
        fprintf(stderr, "Usage: %s <string> <file>\n", argv[0]);
        closelog();
        return 1;
    }

    char *writestr = argv[1];
    char *writefile = argv[2];

   
    FILE *fp = fopen(writefile, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Error: Failed to open file %s: %s", writefile, strerror(errno));
        perror("Error opening file");
        closelog();
        return 1;
    }

    
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    
    if (fprintf(fp, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error: Failed to write to file %s: %s", writefile, strerror(errno));
        perror("Error writing to file");
        fclose(fp);
        closelog();
        return 1;
    }

    
    fclose(fp);
    closelog();

    return 0;
}
