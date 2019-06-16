#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define NO_DEBUG 0
#define LOW 1
#define MEDIUM 2
#define HIGH 3
#define DEBUG_LEVEL HIGH

void debugHigh(const char *format, ...);
void debugMedium(const char *format, ...);
void debugLow(const char *format, ...);

int main(void){
    FILE *addres_file = fopen("addresses.txt","rb");
    int *address = (int*)malloc(sizeof(int));
    int address_length = 0;

    // Read all the address file
    while(fscanf(addres_file, "%d", &address[address_length]) != EOF){
        debugHigh("Saved Address[%d] = %d\n", address_length, address[address_length]);
        address_length++;
        address = realloc(address, ((address_length+1)*sizeof(int)));
    }
    fclose(addres_file);

    free(address);
    return(0);
}

void debugHigh(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    if (DEBUG_LEVEL >= HIGH)
        vfprintf(stdout, format, arg);
    va_end(arg);
}

void debugMedium(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    if (DEBUG_LEVEL >= MEDIUM)
        vfprintf(stdout, format, arg);
    va_end(arg);
}

void debugLow(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    if (DEBUG_LEVEL >= LOW)
        vfprintf(stdout, format, arg);
    va_end(arg);
}