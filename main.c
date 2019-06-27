#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define NO_DEBUG 0
#define LOW 1
#define MEDIUM 2
#define HIGH 3
#define DEBUG_LEVEL HIGH

#define ADDRESS_CLEAN 0xFFFF
#define OFFSET_CLEAN 0xFF
#define TLB_LENGTH 16
#define FRAME_SIZE 256

void readBacking(int pageNumber, FILE *backing_store, char *buffer);

void debugHigh(const char *format, ...);
void debugMedium(const char *format, ...);
void debugLow(const char *format, ...);

int main(void)
{
    FILE *addres_file = fopen("addresses.txt", "rb");
    FILE *backing_store = fopen("BACKING_STORE.bin", "rb");
    int *address = (int *)malloc(sizeof(int));
    int address_length = 0;

    int pageTLB[TLB_LENGTH];
    int frameTLB[TLB_LENGTH];

    int pageTable[FRAME_SIZE];
    int pageFrame[FRAME_SIZE];
    int tlbHits = 0;
    int pageFaults = 0;
    int firstPageTable = 0;
    int memory[FRAME_SIZE][FRAME_SIZE];

    for (int x = 0; x < TLB_LENGTH; x++)
    {
        pageTLB[x] = 0;
        frameTLB[x] = 0;
    }

    // Read all the address file
    // Coloco num vetor de address
    while (fscanf(addres_file, "%d", &address[address_length]) != EOF)
    {
        debugHigh("Saved Address[%d] = %d\n", address_length, address[address_length]);
        address_length++;
        address = realloc(address, ((address_length + 1) * sizeof(int)));
    }

    int page, offset;
    //  Começar a processar percorrendo todos os address
    for (int address_index = 0; address_index < address_length; address_index++)
    {
        // pra cada address separa o page e o offset
        page = ((address[address_index] & ADDRESS_CLEAN) >> 8);
        offset = (address[address_index] & OFFSET_CLEAN);

        int indexTLB;
        int hasHitted = 0;

        // Verifica se a pagina tá na tabela de TLB, se tiver coloca hasHitted pra 1
        for (indexTLB = 0; indexTLB < TLB_LENGTH; indexTLB++)
        {
            // hit check
            if (page == pageTLB[indexTLB])
            {
                hasHitted = frameTLB[indexTLB];
                tlbHits++;
            }
        }

        char buffer[FRAME_SIZE];
        // Se nao tava no TLB procurar no backing
        if (!hasHitted)
        {
            // Procura no pageTable
            for (int x = 0; x < firstPageTable; x++)
            {
                if (hasHitted == pageTable[x])
                {
                    hasHitted = pageFrame[x];
                }
                // Insert to TLB
                // Você precisa inserir + também deve garantir que nao dara um segmentation fault
            }
            // Nao achou nem no tlb nem na table
            if (!hasHitted)
            {
                readBacking(page, backing_store, buffer);
                pageFaults++;
                hasHitted = firstPageTable - 1;
                debugHigh("\nthe readed page %d backing", page);
                for (int i = 0; i < FRAME_SIZE; i++)
                {
                    memory[firstPageTable][i];
                    debugHigh(" %d ", buffer[i]);
                }

                // Insert to TLB
                // Você precisa inserir + também deve garantir que nao dara um segmentation fault
            }
        }
    }

    fclose(addres_file);
    fclose(backing_store);

    free(address);
    return (0);
}

void readBacking(int pageNumber, FILE *backing_store, char *buffer)
{
    if (fseek(backing_store, pageNumber * FRAME_SIZE, SEEK_SET) != 0)
    {
        fprintf(stderr, "Error while searching for page\n");
    }

    if (fread(buffer, sizeof(signed char), FRAME_SIZE, backing_store) == 0)
    {
        fprintf(stderr, "Error while reading the line\n");
    }
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