#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "battery"

#define CAPACITY_FILE "/sys/class/power_supply/BAT0/capacity"

int battery_capacity();
char* battery_status();


int main(int argc, char **argv) {
    if (argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }
   	
	int capacity = battery_capacity();
	char *status = battery_status();

	printf("%d%% %s\n", capacity, status);
	free(status);
}

char* battery_status() {
	char status[265];
	FILE *status_fd = NULL;

	if ((status_fd = fopen("/sys/class/power_supply/BAT0/status", "r")) == NULL){
		perror("error openning file");
		return NULL;
	}

	if ((fgets(status, 256, status_fd)) == NULL) {
		perror("error reading file");
		fclose(status_fd);
		return NULL;
	}
	fclose(status_fd);
	return strdup(status);
}

int battery_capacity() {
    int battery_cap = 0;

    FILE *cap_fd = NULL;

    if ((cap_fd = fopen(CAPACITY_FILE, "r")) == NULL) {
		perror("Error openning file");
		perror(CAPACITY_FILE);
	return -1;
    }
    
    if ((fscanf(cap_fd, "%d", &battery_cap) != 1)) {
  		perror("Error reading file");
		fclose(cap_fd);
	return -2;
    }
    fclose(cap_fd);
    return battery_cap;
}
