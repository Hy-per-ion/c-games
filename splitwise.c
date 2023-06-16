#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char key[2];
    double value;
} KeyValuePair;

void findPath(KeyValuePair* details, int size);
char* getKeyFromValue(KeyValuePair* details, double value, int size);
double roundNumber(double value, int places);

int main() {
    KeyValuePair parm[] = {
        {"A", -5.0},
        {"B", 25.0},
        {"C", -20.0},
        {"D", 25.0},
        {"E", -20.0},
        {"F", -5.0}
    };
    int size = sizeof(parm) / sizeof(parm[0]);

    findPath(parm, size);

    return 0;
}

void findPath(KeyValuePair* details, int size) {
    double max_value = details[0].value;
    double min_value = details[0].value;
    for (int i = 1; i < size; i++) {
        if (details[i].value > max_value) {
            max_value = details[i].value;
        }
        if (details[i].value < min_value) {
            min_value = details[i].value;
        }
    }

    if (max_value != min_value) {
        char* max_key = getKeyFromValue(details, max_value, size);
        char* min_key = getKeyFromValue(details, min_value, size);
        double result = max_value + min_value;
        result = roundNumber(result, 1);

        if (result >= 0.0) {
            printf("%s needs to pay %s: %.2f\n", min_key, max_key, fabs(min_value));
            for (int i = 0; i < size; i++) {
                if (strcmp(details[i].key, max_key) == 0) {
                    details[i].value = result;
                }
                if (strcmp(details[i].key, min_key) == 0) {
                    details[i].value = 0.0;
                }
            }
        }
        else {
            printf("%s needs to pay %s: %.2f\n", min_key, max_key, fabs(max_value));
            for (int i = 0; i < size; i++) {
                if (strcmp(details[i].key, max_key) == 0) {
                    details[i].value = 0.0;
                }
                if (strcmp(details[i].key, min_key) == 0) {
                    details[i].value = result;
                }
            }
        }

        findPath(details, size);
    }
}

char* getKeyFromValue(KeyValuePair* details, double value, int size) {
    for (int i = 0; i < size; i++) {
        if (details[i].value == value) {
            return details[i].key;
        }
    }
    return NULL;
}

double roundNumber(double value, int places) {
    double factor = pow(10.0, places);
    return round(value * factor) / factor;
}
