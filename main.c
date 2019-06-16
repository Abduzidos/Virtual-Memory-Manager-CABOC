#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *addres_file = fopen("addresses.txt","rb");
    int *address = (int*)malloc(sizeof(int));
    int address_length = 0;

    // Read all the address file
    while(fscanf(addres_file, "%d", &address[address_length]) != EOF){
        address_length++;
        address = realloc(address, ((address_length+1)*sizeof(int)));
    }
    fclose(addres_file);

    free(address);
    return(0);
}