#include <stdio.h>
#include <stdlib.h>

#define MAX_HOTELS_NUM 50
#define MAX_NAME_CHARS 50

int main()
{
    char* hotel_name[MAX_HOTELS_NUM]; // Declare an array of pointer to store the each names of the hotel

    // Allocate maximum 50 characters for each name
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        hotel_name[i] = (char*)malloc(MAX_NAME_CHARS * sizeof(char)); 
    }

    
    
    return 0;
}