#include <stdio.h> // Standard input output library for scanning user inputs
#include <stdlib.h>
#include <stdbool.h> // Boolean library for loop flags

#define MAX_HOTELS_NUM 50
#define MAX_NAME_CHARS 50
#define INF 999999

// Obtains user input for the menu choices
// Checks for correct inputs 
// Returns value if correct
int obtainUserInputMenu() 
{
    bool loop_flag = true;

    while (loop_flag)
    {
        char user_input_string[10];
        
        printf("\nEnter your choice: ");

        fgets(user_input_string, sizeof(user_input_string), stdin);

        // Convert string to int if not numbers are detected, returns 0
        int user_input = atoi(user_input_string);

        if (user_input == 0) // No numbers detected in user input
        {
            printf("\nError. Please enter a number.\n");
        }

        if (user_input >= 1 && user_input <= 9)
        {
            return user_input;
        }
        else // Numbers inputed are not from 1 to 9
        {
            printf("\nError. You can only enter a number from 1 - 9.\n");
        }
    }
}

// Display the menu and read user input 
// Returns user input
int displayMenuAndReadInput()
{
    printf("\n===== Smart Travel Planner System =====\n");
    printf("1. Add Hotel\n");
    printf("2. View All Hotels\n");
    printf("3. Sort Hotels by Price (Bubble Sort)\n");
    printf("4. Sort Hotels by Rating (Merge Sort)\n");
    printf("5. Search Hotel by Name (Binary Search)\n");
    printf("6. Select Optimal Hotels within Budget (Knapsack)\n");
    printf("7. Add Path between Hotels\n");
    printf("8. Find Shortest Path Between Hotels (Dijkstra)\n");
    printf("9. Exit\n");
    
    int user_input = obtainUserInputMenu();

    return user_input;
}

// Function to free all pointers with the allocated memory on the heap
void freeAllPointers(char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_distance, int** hotel_paths)
{
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        free(&(hotel_name[i]));
    }

    free(hotel_price);

    free(hotel_rating);

    free(hotel_cityCenter_distance);

    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        free(&(hotel_paths[i]));
    }
}

int main()
{
    char *hotel_name[MAX_HOTELS_NUM]; // Declare an array of pointer to store the each names of the hotel

    // Allocate memory for maximum 51 characters for each hotel name + 1 for the null character
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        hotel_name[i] = (char *)malloc((MAX_NAME_CHARS+1) * sizeof(char)); 
    }

    // Allocate memory to store an array of hotel price without cents (unit: RM)
    int *hotel_price = (int *)malloc(MAX_HOTELS_NUM * sizeof(int)); 

    // Allocate memory to store an array of hotel rating from 1 star to 5 star
    int *hotel_rating = (int *)malloc(MAX_HOTELS_NUM * sizeof(int));

    // Allocate memory to store an array of hotel distance from city center (unit: meters)
    int *hotel_cityCenter_distance = (int *)malloc(MAX_HOTELS_NUM * sizeof(int));

    int *hotel_paths[MAX_HOTELS_NUM]; // Declare an array of pointers to store each path between hotels

    // Allocate memory for storing each path and distance between hotels
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        hotel_paths[i] = (int *)malloc(MAX_HOTELS_NUM * sizeof(int));
    }

    // Boolean flag to check whether to keep running the menu program
    bool menu_loop_flag = true;

    while (menu_loop_flag)
    {
        int user_input = displayMenuAndReadInput();
        
        switch (user_input)
        {
        case 1:
            printf("\nIn 1");
            break;
        
        case 2:
            printf("\nIn 2");
            break;
        
        case 3:
            printf("\nIn 3");
            break;
        
        case 4:
            printf("\nIn 4");
            break;
        
        case 5:
            printf("\nIn 5");
            break;
        
        case 6:
            printf("\nIn 6");
            break;
        
        case 7:
            printf("\nIn 7");
            break;
        
        case 8:
            printf("\nIn 8");
            break;
        
        case 9: 
            printf("\nThank you for using the Smart Travel Planner System");
            printf("\nWe hope you have a great time travelling!\n");

            // Exits the loop and end program
            menu_loop_flag = false;

            break;

        default:
            printf("\nError. Input does not match.\n");
            break;
        }
    }

    // Free all pointers with memory allocated on heap
    freeAllPointers(hotel_name, hotel_price, hotel_rating, hotel_cityCenter_distance, hotel_paths);

    return 0;
}