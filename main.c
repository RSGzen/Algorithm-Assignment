#include <stdio.h> // Standard input output library for scanning user inputs
#include <stdlib.h>
#include <stdbool.h> // Boolean library for loop flags
#include <string.h> // String library
#include <time.h> // Time library for random ID generation

#define MAX_HOTELS_NUM 50
#define MAX_NAME_CHARS 51
#define INF 99999

// It ain't much work but it's honest work
void printLine()
{
    printf("\n---------------------------------");
}

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
        
        if (fgets(user_input_str, 10, stdin) != NULL) // fgets would not return NULL if read until max character limits
        {
            if (strchr(user_input_str, '\n') == NULL) // Check if the newline char was found indicating until max characters was read
            {
                // If no newline character to be found, more characters are inputted than the allowed limit
                while (getchar() != '\n'); // Discard remaining characters in the input buffer until the newline
            }
        }
        
        user_input = atoi(user_input_str);

        if (user_input == 0) // No numbers detected in user input
        {
            printf("\nError. Please enter a number.\n");
            printLine();
        }
        else
        {
            if (user_input >= lower_bound && user_input <= upper_bound)
        {
            return user_input;
        }

            else // Numbers inputed are not between lower bound and upper bound
            {
                printf("\nError. You can only enter a number from %d - %d.\n", lower_bound, upper_bound);
                printLine();
            }
        }
    }
}

void userInputString(char* input_message, char** arr_to_store, int current_hotel_idx)
{
    char user_input_str[MAX_NAME_CHARS];
    
    printf("\n%s", input_message);

    if (fgets(user_input_str, MAX_NAME_CHARS, stdin) != NULL) // Check if there are more characters inputted than the chars read by fgets
    {
        if (strchr(user_input_str, '\n') == NULL) // Check if the newline char was found indicating until max characters was read
        {
            // If no newline character to be found, more characters are inputted than the allowed limit
            while (getchar() != '\n'); // Discard remaining characters in the input buffer until the newline
        }
    }

    // Replace the character with null character it so that when printing it would not affect the format
    
    bool checkIfStrIsFull = true;

    for (int i = 0; i < MAX_NAME_CHARS; i++)
    {
        if (user_input_str[i] == '\n')
        {
            user_input_str[i] = '\0';
            checkIfStrIsFull = false;
        }
    }

    if (checkIfStrIsFull == true)
    {
        user_input_str[MAX_NAME_CHARS-1] = '\0';
    }

    // Copy input into the array
    strcpy(arr_to_store[current_hotel_idx], user_input_str);
}

// Display the menu and read user input 
// Returns user input
int displayMenuAndReadInput()
{
    printf("\n======================================== Smart Travel Planner System =========================================\n\n");
    printf("\t1. Add Hotel\n");
    printf("\t2. View All Hotels\n");
    printf("\t3. Sort Hotels by Price (Bubble Sort)\n");
    printf("\t4. Sort Hotels by Rating (Merge Sort)\n");
    printf("\t5. Search Hotel by Name (Binary Search)\n");
    printf("\t6. Select Optimal Hotels within Budget (Knapsack)\n");
    printf("\t7. Add Path between Hotels\n");
    printf("\t8. Find Shortest Path Between Hotels (Dijkstra)\n");
    printf("\t9. Exit\n");
    
    char message[] = "Enter your choice: ";

    int user_input = userInputInt(message, 1, 9);

    printf("\n========================================      Now in Choice %d      =========================================\n", user_input);

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

    char message_name[] = "Enter the name of hotel (Max 50 characters): ";
    char message_price[] = "Enter the price of hotel (without cents): ";
    char message_rating[] = "Enter the rating of hotel (stars): ";
    char message_distance[] = "Enter the distance of hotel from city center (meters): ";
    
    for (int i = current_num_hotels; i < num_hotels ; i++)
    {
        printf("\n------- Details of Hotel %d -------\n", i+1);

        // Use current time as seed
        srand(time(NULL));

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

void addPathToHotels(int current_num_hotels, char** hotel_name, int** hotel_paths)
{
    // Check if current number of hotels are greater than or equal to 2 if not then path cannot be established
    if (current_num_hotels >= 2)
    {
        // Print out hotels name to choose from
        printf("\n| No. |                     Hotel Name                     |\n");

        for (int i = 0; i < current_num_hotels; i++)
        {
            printf("%-2d. %-50s\n", i+1, hotel_name[i]);    
        }

        char message1[] = "Enter your first choice of hotel: ";
        char message2[] = "Enter your second choice of hotel: ";

        // Obtain first hotel choice input
        int user_first_input = userInputInt(message1, 1, current_num_hotels);
        int user_second_input;

        while (true)
        {
            // Obtain second hotel choice input
            user_second_input = userInputInt(message2, 1, current_num_hotels);

            // Break out of loop if both inputs are not same
            if (user_first_input != user_second_input)
            {
                break;
            }
            else
            {
                printf("\nThe hotels choosen cannot be the same. \nPlease try again.\n");
            }
        }

        char message3[] = "Enter the distance of the path between 2 hotels choosen (1m - 10000m): ";

        int user_dist_input = userInputInt(message3, 1, 10000);

        hotel_paths[user_first_input-1][user_second_input-1] = user_dist_input;
        hotel_paths[user_second_input-1][user_first_input-1] = user_dist_input;

        printf("\nSucessfully recorded. \n");

    }
    else
    {
        printf("\nCurrent number of hotels recorded are less than 2.\n You cannot establish any path between hotels.\n");
    }
}

// Function to view hotel from the perspective of number, ID, name, price, rating, distance from city center
void viewHotels(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist, int** hotel_paths)
{
    // If current number of hotels are 0, do not print viewing table
    if (current_num_hotels != 0)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Details of Hotels ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("| No. |     ID     |                     Hotel Name                     |   Price  | Rating |  Distance |\n");

        for (int i = 0; i < current_num_hotels; i++)
        {
            printf("| %-2d  |", i+1); // Print No.
            printf(" %-10d |", hotel_id[i]); // Print hotel ID
            printf(" %-50s |", hotel_name[i]);
            printf(" RM %-5d |", hotel_price[i]);
            printf(" %d star |", hotel_rating[i]);
            printf("  %-5d m  |\n", hotel_cityCenter_dist[i]);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Distance Between Hotels ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        printf("|      ");

        for (int i = 0; i < current_num_hotels; i++)
        {
            printf("|  %-2d   ", i+1);
        }

        printf("|\n");

        for (int i = 0; i < current_num_hotels; i++)
        {
            printf("| %-2d   ", i+1);

            for (int j = 0; j < current_num_hotels; j++)
            {
                printf("| %-5d ", hotel_paths[i][j]);
            }

            printf("|\n");
        }
        printf("\n*Note: 99999 means path between 2 hotels are non-existance\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }

    else
    {
        printf("\nCurrent number of hotels are 0.\n Please enter hotel informations before viewing.\n");
        printLine();
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

    // Initialize all hotel paths to be non-existent by using self declared infinity 
    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        for (int j = 0; j < MAX_HOTELS_NUM; j++)
        {
            hotel_paths[i][j] = INF;
        }
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
            viewHotels(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist, hotel_paths);

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
            addPathToHotels(current_num_hotels, hotel_name, hotel_paths);

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