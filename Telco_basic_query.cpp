#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PHONE_LENGTH 11
#define MAX_DATE_LENGTH 11
#define MAX_TIME_LENGTH 9
#define MAX_CALLS 1000000

typedef struct {
    char from_number[MAX_PHONE_LENGTH];
    char to_number[MAX_PHONE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char from_time[MAX_TIME_LENGTH];
    char end_time[MAX_TIME_LENGTH];
} Call;

Call calls[MAX_CALLS];
int call_count = 0;

bool is_valid_phone_number(const char* number) {
    for (int i = 0; i < 10; i++) {
        if (number[i] < '0' || number[i] > '9') {
            return false;
        }
    }
    return true;
}

int time_to_seconds(const char* time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int duration_in_seconds(const char* from_time, const char* end_time) {
    return time_to_seconds(end_time) - time_to_seconds(from_time);
}

void process_calls() {
    char line[100];
    while (fgets(line, sizeof(line), stdin) && line[0] != '#') {
        sscanf(line, "call %s %s %s %s %s", 
               calls[call_count].from_number,
               calls[call_count].to_number,
               calls[call_count].date,
               calls[call_count].from_time,
               calls[call_count].end_time);
        call_count++;
    }
}

int get_call_count(const char* number) {
    int count = 0;
    for (int i = 0; i < call_count; i++) {
        if (strcmp(calls[i].from_number, number) == 0) {
            count++;
        }
    }
    return count;
}

int get_total_duration(const char* number){
    int total_duration = 0;
    for (int i = 0; i < call_count; i++) {
        if (strcmp(calls[i].from_number, number) == 0) {
            total_duration += duration_in_seconds(calls[i].from_time, calls[i].end_time);
        }
    }
    return total_duration;
}

void process_queries() {
    char line[100];
    while (fgets(line, sizeof(line), stdin) && line[0] != '#') {
        if (strcmp(line, "?check_phone_number\n") == 0) {
            bool all_valid = true;
            for (int i = 0; i < call_count; i++) {
                if (!is_valid_phone_number(calls[i].from_number) || 
                    !is_valid_phone_number(calls[i].to_number)) {
                    all_valid = false;
                    break;
                }
            }
            printf("%d\n", all_valid ? 1 : 0);
        } else if (strncmp(line, "?number_calls_from ", 19) == 0) {
            char number[MAX_PHONE_LENGTH];
            sscanf(line, "?number_calls_from %s", number);
            printf("%d\n", get_call_count(number));
        } else if (strcmp(line, "?number_total_calls\n") == 0) {
            printf("%d\n", call_count);
        } else if (strncmp(line, "?count_time_calls_from ", 23) == 0) {
            char number[MAX_PHONE_LENGTH];
            sscanf(line, "?count_time_calls_from %s", number);
            printf("%d\n", get_total_duration(number));
        }
    }
}

int main() {
    process_calls();
    process_queries();
    return 0;
}