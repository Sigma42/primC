//
// Created by sigma42 on 31.12.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u_int getSize(FILE* file);

int main() {

    FILE *file = fopen("prim.data", "rb");
    u_int size = getSize(file);
    int ans;
    size_t d0;
    int d1;

    u_int * primList = malloc(size);

    printf("Size: %u\n\n",size/4);
    d1 = scanf("%i", &ans);

    if (size/4 >= ans) size = (u_int)ans;
    else size = size/4;

    d0 = fread(primList, size, 4, file);
    for (u_int i=0;i < size;i++) {
        printf("%u\n",primList[i]);
    }

    fclose(file);
    free(primList);
}

u_int getSize(FILE* file) {

    fseek(file, 0L, SEEK_END);
    u_int size = (u_int)ftell(file);
    rewind(file);

    return size;
}