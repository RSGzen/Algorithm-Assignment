#include <stdio.h> // Standard input output library for scanning user inputs
#include <stdlib.h>
#include <stdbool.h> // Boolean library for loop flags

#define MAX_HOTELS_NUM 50
#define MAX_NAME_CHARS 50
#define INF 999999

// Obtain user input and converts it to type integer
// Check for whether integer is between lower bound and upper bound
// If not repeat and demand input
int userInputInt(char* input_message, int lower_bound, int upper_bound)
{
    bool input_flag = true;
    char user_input_str[10];
    int user_input;

    while (input_flag)
    {
        printf("\n%s", input_message);
        
        fgets(user_input_str, 10, stdin);

        user_input = atoi(user_input_str);

        if (user_input == 0) // No numbers detected in user input
        {
            printf("\nError. Please enter a number.\n");
        }

        if (user_input >= lower_bound && user_input <= upper_bound)
        {
            return user_input;
        }

        else // Numbers inputed are not between lower bound and upper bound
        {
            printf("\nError. You can only enter a number from %d - %d.\n", lower_bound, upper_bound);
        }
    }
}

void userInputString(char* input_message, char** arr_to_store, int current_hotel_idx)
{
    char user_input_str[MAX_NAME_CHARS];
    
    printf("\n%s", input_message);

    fgets(arr_to_store[current_hotel_idx], MAX_NAME_CHARS-1, stdin);
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
    
    char message[] = "Enter your choice: ";

    int user_input = userInputInt(message, 1, 9);

    return user_input;
}

// Function to free all pointers with the allocated memory on the heap
void freeAllPointers(int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist, int** hotel_paths)
{
    free(hotel_id);
    
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        free(&(hotel_name[i]));
    }

    free(hotel_price);

    free(hotel_rating);

    free(hotel_cityCenter_dist);

    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        free(&(hotel_paths[i]));
    }
}

// Function to add hotels and input their information
int addHotels(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist)
{
    char message[] = "Enter the number of hotels to record: ";

    // Obtain user input about the amount of hotels to record at a time
    int num_hotels = userInputInt(message, 1, 10);

    char message_name[] = "Enter the name of hotel: ";
    char message_price[] = "Enter the price of hotel (without cents): ";
    char message_rating[] = "Enter the rating of hotel (stars): ";
    char message_distance[] = "Enter the distance of hotel from city center (meters): ";
    
    for (int i = current_num_hotels; i < num_hotels ; i++)
    {
        printf("\n------- Details of Hotel %d -------\n", i+1);

        // Generate a random number for ID and stored
        hotel_id[i] = rand();

        // User input hotel name and stored
        userInputString(message_name, hotel_name, i);

        // User input hotel price and stored
        // Price minimum RM 1 and maximum RM 10000
        // Price cannot have cents because it is stored as float
        hotel_price[i] = userInputInt(message_price, 1, 10000);

        // User input hotel rating and stored
        // Rating minimum 1 star and maximum 5 star
        hotel_rating[i] = userInputInt(message_rating, 1, 5);

        // User input hotel distance from city center and stored
        // Distance are in units of meters
        // Distance minimum 1m and maximum of 10,000m (10km)
        hotel_cityCenter_dist[i] = userInputInt(message_distance, 1, 10000);
    }

    // Update the current number of hotels
    current_num_hotels += num_hotels;

    return current_num_hotels;
}

void viewHotels(int current_num_hotels, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist)
{
    // If current number of hotels are 0, do not print viewing table
    if (current_num_hotels != 0)
    {
        printf("\n~~~~~~~~~~~~~ Details of Hotels ~~~~~~~~~~~~~\n");
        pritnf("\n");
        
        for (int i = 0; i < current_num_hotels; i++)
        {
            printf("\n%d");
        }
    }
    else
    {
        printf("\nCurrent number of hotels are 0.\n Please enter hotel informations before viewing.\n");
    }
}

int main()
{
    int current_num_hotels = 0;

    int *hotel_id = (int *)malloc(MAX_HOTELS_NUM * sizeof(int));
    
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
    int *hotel_cityCenter_dist = (int *)malloc(MAX_HOTELS_NUM * sizeof(int));

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
            current_num_hotels = addHotels(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist);

            break;
        
        case 2:
            printf("\nIn 2\n");
            break;
        
        case 3:
            printf("\nIn 3\n");
            break;
        
        case 4:
            printf("\nIn 4\n");
            break;
        
        case 5:
            printf("\nIn 5\n");
            break;
        
        case 6:
            printf("\nIn 6\n");
            break;
        
        case 7:
            printf("\nIn 7\n");
            break;
        
        case 8:
            printf("\nIn 8\n");
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
    freeAllPointers(hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist, hotel_paths);

    return 0;
}