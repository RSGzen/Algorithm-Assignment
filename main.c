#include <stdio.h> // Standard input output library for scanning user inputs
#include <stdlib.h>
#include <stdbool.h> // Boolean library for loop flags
#include <string.h> // String library
#include <time.h> // Time library for random ID generation
#include <ctype.h> // For use in the strcasecmp function

#define MAX_HOTELS_NUM 50 // Maximum number of hotels predefined
#define MAX_NAME_CHARS 51 // Maximum number of characters allowed per hotel name (50 chars + 1 null character)
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
        free(hotel_name[i]);
    }

    free(hotel_name);

    free(hotel_price);

    free(hotel_rating);

    free(hotel_cityCenter_dist);

    for (int i = 0; i < MAX_HOTELS_NUM; i++)
    {
        free(hotel_paths[i]);
    }

    free(hotel_paths);
}

// Function to add hotels and input their information
int addHotels(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist)
{
    char message[] = "Enter the number of hotels to record: ";

    // Obtain user input about the amount of hotels to record at a time
    int num_hotels = userInputInt(message, 1, 10);

    // Check whether 
    if (num_hotels + current_num_hotels > MAX_HOTELS_NUM)
    {
        printf("\nNumber of hotels data wished to enter has exceed database limits");
        printf("\nMaximum number of hotel data permitted to saved in database is %d hotels.\n", MAX_HOTELS_NUM);
        
        return MAX_HOTELS_NUM;
    }

    char message_name[] = "Enter the name of hotel (Max 50 characters): ";
    char message_price[] = "Enter the price of hotel (without cents): ";
    char message_rating[] = "Enter the rating of hotel (stars): ";
    char message_distance[] = "Enter the distance of hotel from city center (meters): ";
    
    for (int i = current_num_hotels; i < num_hotels + current_num_hotels; i++)
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
            printf("| %-2d. | %-50s |\n", i+1, hotel_name[i]);    
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

// Function to view sorted and search hotel
void viewSortSearchHotels(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist)
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
            printf(" %-50s |", hotel_name[i]);// Print hotel Name
            printf(" RM %-5d |", hotel_price[i]);//Print hotel Price
            printf(" %d star |", hotel_rating[i]);//Print hotel Rating
            printf("  %-5d m  |\n", hotel_cityCenter_dist[i]);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }

    else
    {
        printf("\nCurrent number of hotels are 0.\n Please enter hotel informations before viewing.\n");
        printLine();
    }
}

// Function to create temporary hotel data for sorting and searching hotel
void createTempHotelData(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist, int** temp_id, char*** temp_name, int** temp_price, int** temp_rating, int** temp_dist) {
    // Allocate memory
    *temp_id = (int*)malloc(current_num_hotels * sizeof(int));
    *temp_price = (int*)malloc(current_num_hotels * sizeof(int));
    *temp_rating = (int*)malloc(current_num_hotels * sizeof(int));
    *temp_dist = (int*)malloc(current_num_hotels * sizeof(int));
    *temp_name = (char**)malloc(current_num_hotels * sizeof(char*));


    for (int i = 0; i < current_num_hotels; i++) {
        (*temp_id)[i] = hotel_id[i];
        (*temp_price)[i] = hotel_price[i];
        (*temp_rating)[i] = hotel_rating[i];
        (*temp_dist)[i] = hotel_cityCenter_dist[i];

        (*temp_name)[i] = (char*)malloc((MAX_NAME_CHARS + 1) * sizeof(char));
        strcpy((*temp_name)[i], hotel_name[i]);
    }
}

//Function to free the memory after use
void freeTempHotelData(int current_num_hotels, int* temp_id, char** temp_name, int* temp_price, int* temp_rating, int* temp_dist) {
    for (int i = 0; i < current_num_hotels; i++) {
        free(temp_name[i]);
    }

    free(temp_name);
    free(temp_id);
    free(temp_price);
    free(temp_rating);
    free(temp_dist);
}

//Function to execute Bubble Sort
void BubleSort(int current_num_hotels, int* temp_id, char** temp_name, int* temp_price, int* temp_rating, int* temp_dist) {
    for(int i = 0; i < current_num_hotels - 1; i++) {  // Changed to current_num_hotels - 1
        for(int j = 0; j < current_num_hotels - i - 1; j++) {  // Changed to current_num_hotels - i - 1
            if(temp_price[j] > temp_price[j+1]) {
                // Swap IDs
                int ti = temp_id[j];
                temp_id[j] = temp_id[j+1];
                temp_id[j+1] = ti;

                // Swap prices
                int tp = temp_price[j];
                temp_price[j] = temp_price[j+1];
                temp_price[j+1] = tp;

                // Swap names - use strcpy with properly allocated memory
                char* tn = temp_name[j];
                temp_name[j] = temp_name[j+1];
                temp_name[j+1] = tn;

                // Swap ratings
                int tr = temp_rating[j];
                temp_rating[j] = temp_rating[j+1];
                temp_rating[j+1] = tr;

                // Swap distances
                int td = temp_dist[j];
                temp_dist[j] = temp_dist[j+1];
                temp_dist[j+1] = td;
            }
        }
    }
}

//Function to prepare data, call bubble sot and show sorted results
void sortByPriceUsingBubble(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist){
    if (current_num_hotels == 0) {
        printf("\nNo hotels available to sort.\n");
        return;
    }

    // Create temp data
    int *temp_id, *temp_price, *temp_rating, *temp_dist;
    char **temp_name;

    createTempHotelData(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist,
                        &temp_id, &temp_name, &temp_price, &temp_rating, &temp_dist);

    // Perform bubble sort by price
    BubleSort(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);

    // Display sorted results
    viewSortSearchHotels(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);

    // Free temp data
    freeTempHotelData(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);
}

// Re-wrote strcasecmp function due to it not available in the C standard library for certain standards
int strcasecmp_rewrite(const char *s1, const char *s2)
{
    int offset,ch;
    unsigned char a,b;

    offset = 0;
    ch = 0;
    while( *(s1+offset) != '\0' )
    {
        /* Check for end of s2 */
        if( *(s2+offset)=='\0')
            return( *(s1+offset) );

        a = (unsigned)*(s1+offset);
        b = (unsigned)*(s2+offset);
        ch = toupper(a) - toupper(b);
        if( ch<0 || ch>0 )
            return(ch);
        offset++;
    }

    return(ch);
}

// Function to allocate memory on heap for an array of integer
int* int_array_allocate(int array_size)
{
    int* array_pointer = (int*)malloc(array_size * sizeof(int));

    return array_pointer;
}

// Function to allocate memory on heap for an array of characters
char** char_array_allocate(int array_size)
{   
    char** array_pointer = (char**)malloc(array_size * sizeof(char*));

    return array_pointer;
}

// Function to free all temp array pointers
void freeMergeTempPointers(int* L_id, int* R_id, int* L_price, int* R_price, int* L_rating, int* R_rating, int* L_dist, int* R_dist, char** L_name, char** R_name, int n1, int n2)
{
    free(L_id);
    free(R_id);

    free(L_price);
    free(R_price);

    free(L_rating);
    free(R_rating);

    free(L_dist);
    free(R_dist);

    for (int i = 0; i < n1; i++)
    {
        free(L_name[i]);
    }

    for (int i = 0; i < n2; i++)
    {
        free(R_name[i]);
    }

    free(L_name);
    free(R_name);
}

// Function to merge sorted subarrays by rating
void mergeByRating(int left, int mid, int right, int* temp_id, char** temp_name, int* temp_price, int* temp_rating, int* temp_dist){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temp arrays
    int* L_id = int_array_allocate(n1);
    int* R_id = int_array_allocate(n2);

    int* L_price = int_array_allocate(n1);
    int* R_price = int_array_allocate(n2);

    int* L_rating = int_array_allocate(n1);
    int* R_rating = int_array_allocate(n2);

    int* L_dist = int_array_allocate(n1);
    int* R_dist = int_array_allocate(n2);

    char** L_name = char_array_allocate(n1);
    char** R_name = char_array_allocate(n2);

    for (int i = 0; i < n1; i++) {
        L_id[i] = temp_id[left + i];
        L_price[i] = temp_price[left + i];
        L_rating[i] = temp_rating[left + i];
        L_dist[i] = temp_dist[left + i];
        L_name[i] = strdup(temp_name[left + i]);
    }

    for (int j = 0; j < n2; j++) {
        R_id[j] = temp_id[mid + 1 + j];
        R_price[j] = temp_price[mid + 1 + j];
        R_rating[j] = temp_rating[mid + 1 + j];
        R_dist[j] = temp_dist[mid + 1 + j];
        R_name[j] = strdup(temp_name[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    //Merge left and right array based on rating(descending)
    while (i < n1 && j < n2) {
        if (L_rating[i] >= R_rating[j]) {
            temp_id[k] = L_id[i];
            temp_price[k] = L_price[i];
            temp_rating[k] = L_rating[i];
            temp_dist[k] = L_dist[i];
            strcpy(temp_name[k], L_name[i]);
            i++;
        } else {
            temp_id[k] = R_id[j];
            temp_price[k] = R_price[j];
            temp_rating[k] = R_rating[j];
            temp_dist[k] = R_dist[j];
            strcpy(temp_name[k], R_name[j]);
            j++;
        }
        k++;
    }

    //Copy any remaining elements from left side
    while (i < n1) {
        temp_id[k] = L_id[i];
        temp_price[k] = L_price[i];
        temp_rating[k] = L_rating[i];
        temp_dist[k] = L_dist[i];
        strcpy(temp_name[k], L_name[i]);
        i++; k++;
    }

    //Copy any remaining elements from right side
    while (j < n2) {
        temp_id[k] = R_id[j];
        temp_price[k] = R_price[j];
        temp_rating[k] = R_rating[j];
        temp_dist[k] = R_dist[j];
        strcpy(temp_name[k], R_name[j]);
        j++; k++;
    }

    freeMergeTempPointers(L_id, R_id, L_price, R_price, L_rating, R_rating, L_dist, R_dist, L_name, R_name, n1, n2);
}

//Function to divide array, recursively sort and merge
void mergeSortByRating(int left, int right, int* temp_id, char** temp_name, int* temp_price, int* temp_rating, int* temp_dist){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByRating(left, mid, temp_id, temp_name, temp_price, temp_rating, temp_dist);
        mergeSortByRating(mid + 1, right, temp_id, temp_name, temp_price, temp_rating, temp_dist);
        mergeByRating(left, mid, right, temp_id, temp_name, temp_price, temp_rating, temp_dist);
    }
}

//Function to prepare data, call sorting and show results
void SortByRatingUsingMerge(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist) {
    if (current_num_hotels == 0) {
        printf("\nNo hotels available to sort.\n");
        return;
    }

    // Create temp data
    int *temp_id, *temp_price, *temp_rating, *temp_dist;
    char **temp_name;

    createTempHotelData(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist,
                        &temp_id, &temp_name, &temp_price, &temp_rating, &temp_dist);

    // Perform merge sort by rating
    mergeSortByRating(0, current_num_hotels - 1, temp_id, temp_name, temp_price, temp_rating, temp_dist);

    // Display sorted results
    viewSortSearchHotels(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);

    // Free temp data
    freeTempHotelData(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);
}

//Functio to find a target name on sorted hotel names
int binarySearchByName(char** temp_name, int current_num_hotels, char* target_name) {
    int left = 0, right = current_num_hotels - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcasecmp_rewrite(temp_name[mid], target_name);

        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void mergeByName(int left, int mid, int right, int* id, char** name, int* price, int* rating, int* dist) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temp arrays
    int* L_id = int_array_allocate(n1);
    int* R_id = int_array_allocate(n2);

    int* L_price = int_array_allocate(n1);
    int* R_price = int_array_allocate(n2);

    int* L_rating = int_array_allocate(n1);
    int* R_rating = int_array_allocate(n2);

    int* L_dist = int_array_allocate(n1);
    int* R_dist = int_array_allocate(n2);

    char** L_name = char_array_allocate(n1);
    char** R_name = char_array_allocate(n2);

    for (int i = 0; i < n1; i++) {
        L_id[i] = id[left + i];
        L_price[i] = price[left + i];
        L_rating[i] = rating[left + i];
        L_dist[i] = dist[left + i];
        L_name[i] = strdup(name[left + i]);
    }
    for (int j = 0; j < n2; j++) {
        R_id[j] = id[mid + 1 + j];
        R_price[j] = price[mid + 1 + j];
        R_rating[j] = rating[mid + 1 + j];
        R_dist[j] = dist[mid + 1 + j];
        R_name[j] = strdup(name[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcasecmp_rewrite(L_name[i], R_name[j]) <= 0) {
            id[k] = L_id[i];
            price[k] = L_price[i];
            rating[k] = L_rating[i];
            dist[k] = L_dist[i];
            strcpy(name[k], L_name[i]);
            i++;
        } else {
            id[k] = R_id[j];
            price[k] = R_price[j];
            rating[k] = R_rating[j];
            dist[k] = R_dist[j];
            strcpy(name[k], R_name[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        id[k] = L_id[i]; price[k] = L_price[i]; rating[k] = L_rating[i]; dist[k] = L_dist[i];
        strcpy(name[k], L_name[i]); i++; k++;
    }
    while (j < n2) {
        id[k] = R_id[j]; price[k] = R_price[j]; rating[k] = R_rating[j]; dist[k] = R_dist[j];
        strcpy(name[k], R_name[j]); j++; k++;
    }

    freeMergeTempPointers(L_id, R_id, L_price, R_price, L_rating, R_rating, L_dist, R_dist, L_name, R_name, n1, n2);
}

//Recursicely divide and merge the hotel data by name using merge sort
void mergeSortByName(int left, int right, int* id, char** name, int* price, int* rating, int* dist) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByName(left, mid, id, name, price, rating, dist);
        mergeSortByName(mid + 1, right, id, name, price, rating, dist);
        mergeByName(left, mid, right, id, name, price, rating, dist);
    }
}

//Function to prepare sorted data, gets user input, perform binary saerching and display results
void searchHotelByName(int current_num_hotels, int* hotel_id, char** hotel_name, int* hotel_price, int* hotel_rating, int* hotel_cityCenter_dist) {
    if (current_num_hotels == 0) {
        printf("\nNo hotels to search.\n");
        return;
    }

    char target_name[MAX_NAME_CHARS];
    char choice;

    // Prepare temp data (we only sort once for performance)
    int *temp_id, *temp_price, *temp_rating, *temp_dist;
    char **temp_name;

    createTempHotelData(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist, &temp_id, &temp_name, &temp_price, &temp_rating, &temp_dist);

    // Sort once before search
    mergeSortByName(0, current_num_hotels - 1, temp_id, temp_name, temp_price, temp_rating, temp_dist);

    do {
        // Prompt user input
        printf("\nEnter the name of hotel to search: ");
        fgets(target_name, MAX_NAME_CHARS, stdin);

        // Remove newline character from input
        char* newline = strchr(target_name, '\n');
        if (newline) *newline = '\0';

        // Perform binary search
        int idx = binarySearchByName(temp_name, current_num_hotels, target_name);

        if (idx != -1) {
            // Hotel found
            printf("\nHotel found!\n");
            printf("|     ID     |                     Hotel Name                     |   Price  | Rating |  Distance |\n");
            printf("| %-10d | %-50s | RM %-5d | %d star |  %-5d m  |\n",
                   temp_id[idx], temp_name[idx], temp_price[idx], temp_rating[idx], temp_dist[idx]);
            break;  // Exit loop after success
        } else {
            // Hotel not found
            printf("\nHotel '%s' not found.", target_name);
            printf("\nWould you like to try again? (Y/N): ");
            scanf(" %c", &choice);
            getchar();  // Clear newline from input buffer

        }
    } while (choice == 'Y' || choice == 'y');

    // Cleanup
    freeTempHotelData(current_num_hotels, temp_id, temp_name, temp_price, temp_rating, temp_dist);
}


// Knapsack function to select best combination of hotels within budget
void knapsack(int n, int budget, int *prices, int *ratings, char **hotel_name, int *selected) {

    // Create DP table
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((budget + 1) * sizeof(int));
    }

    // Initialize DP table
    for (int row = 0; row <= n; row++) {
        for (int col = 0; col <= budget; col++) {
            if (row == 0 || col == 0) {
                //if both col and row is 0 then value is 0
                dp[row][col] = 0;
            } 
            
            else if (prices[row - 1] <= col) {   

                // 2 variable used to determine if the hotel is included
                // (current hotel rating + prev row's remaining money,col) comapre (value at the col above)
                int include = ratings[row - 1] + dp[row - 1][col - prices[row - 1]];  
                int exclude = dp[row - 1][col];

                if (include > exclude){  //choose the larger
                    dp[row][col] = include;
                } else{
                    dp[row][col] = exclude;
                }

            } else {  //current price > col 
                dp[row][col] = dp[row - 1][col];  //copy value from the above row
            }
        }
    }

    // Backtrack to find selected hotels
    int row = n, col = budget; //(start from the last element in the table)
    while (row > 0 && col >= 0) {
        if (row == 0 || col == 0) break;

        if (dp[row][col] == dp[row - 1][col]) { //it means current hotel is not included
            row--;

        } else {                                //it means current hotel is included
            selected[row - 1] = 1;  //mark current hotal as include
            col -= prices[row - 1]; //go to the remaining money, col
            row--;
        }
    }

    // Print results
    printf("\nMaximum rating achievable: %d\n", dp[n][budget]);
    
    int any_selected = 0;
    printf("\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Selected Hotel for Knapsnack~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("| No. |                  Hotel Name                        |  Price      |   Rating    |\n");
    for (int i = 0; i < n; i++) {
        if (selected[i]) {
            printf("| %-2d  |", i+1);
            printf(" %-50s |",hotel_name[i]);
            printf("  %-10d |",prices[i] );
            printf("  %-10d |\n",ratings[i] );
            any_selected = 1;
        }
    }
    if (!any_selected) {
        printf("None");
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

// Find shortest distance between hotels using Dijkstra's Algorithm
int dijkstra(int** adjMatrix, int numHotels, int start, int end, int*prev ) {
    int visited[MAX_HOTELS_NUM] = {0}; // track which hotel have been visited
    int distance[MAX_HOTELS_NUM]; // store shortest distance 

    for (int i = 0; i < numHotels; i++) {
        distance[i] = INF; 
        prev[i] = -1; // -1 means no value yet
    }
    distance[start] = 0; // set distance at starting point 0

    for (int count = 0; count < numHotels - 1; count++) {
        int minDist = INF, u = -1;
        for (int i = 0; i < numHotels; i++) {
            if (!visited[i] && distance[i] < minDist) { // find the smallest distance between unvisited hotels
                minDist = distance[i];
                u = i;
            }
        }

        if (u == -1 || u == end) break; // if no hotel found or at ending point , it will break 

        visited[u] = 1; // mark hotel u visited 

        for (int v = 0; v < numHotels; v++) { //check the path through u is shorter than the current distance v
            if (!visited[v] && adjMatrix[u][v] != INF && distance[u] + adjMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adjMatrix[u][v];
                prev[v] = u;// to set u as the previous path in prev[v]
            }
        }
    }

    return distance[end]; //return shortest distance to the end, else it will be INF
}

// Find shortest path between hotels
void findShortestPath(int current_num_hotels, char** hotel_name, int** hotel_paths) {
    if (current_num_hotels >= 2) { // make sure there is at least 2 hotel 
        printf("\n| No. |                     Hotel Name                     |\n");
        for (int i = 0; i < current_num_hotels; i++) {
            printf("| %-2d. | %-50s |\n", i+1, hotel_name[i]);
        }

        char message1[] = "Enter the starting hotel: ";
        char message2[] = "Enter the ending hotel: ";

        int starting = userInputInt(message1, 1, current_num_hotels) - 1; // get user's choice of starting hotel 
        int ending;

        while (true) {
            ending = userInputInt(message2, 1, current_num_hotels) - 1; // -1 to 0 based index
            if (starting != ending) { //check ending hotel to make sure is different from the starting one
                break;
            } else {
                printf("\nStarting and Ending hotels cannot be the same.\nPlease try again.\n");
            }
        }

        int prev [MAX_HOTELS_NUM]; //array to store previous path 
        int shortestDistance = dijkstra(hotel_paths, current_num_hotels, starting, ending, prev); // call dijkstra function to find the shortest distance

        if (shortestDistance == INF) { //if INF then let user now there is no path between selected hotels
            printf("\nThere is no path from %s to %s.\n", hotel_name[starting], hotel_name[ending]);
        } else {
            printf("\nShortest distance from %s to %s is: %d meters\n", hotel_name[starting], hotel_name[ending], shortestDistance);
            printf("Path : ");
            int path[MAX_HOTELS_NUM], pathLen = 0;
            for (int v = ending; v != -1; v = prev[v]) { //start at ending and end at -1 which is the starting point
                path[pathLen++] = v; //store path array in reverse order
            }
            for (int i = pathLen - 1; i >= 0; i--) { //iterate path backward to print in a correct order
                printf("%s", hotel_name[path[i]]);
                if (i > 0) {
                  printf(" -> ");
                }
            }
            printf("\n");
        }
    } else {
        printf("\nCurrent number of hotels is less than 2.\nYou cannot find a path between hotels.\n");
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
            sortByPriceUsingBubble(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist);

            break;
        
        case 4:
            SortByRatingUsingMerge(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist);

            break;
        
        case 5:
            searchHotelByName(current_num_hotels, hotel_id, hotel_name, hotel_price, hotel_rating, hotel_cityCenter_dist);

            break;
        
        case 6:
            if (current_num_hotels == 0) {  // Error handling 
                printf("\nNo hotels available. Please add hotels first.\n");
                printLine();
            } else {

                char message[] = "Enter your budget: ";
                int budget = userInputInt(message, 1, 99999);
                int *selected = (int *)malloc(current_num_hotels * sizeof(int));  //dynamic array to trach which hotel is chosen
                for (int i = 0; i < current_num_hotels; i++) {
                    selected[i] = 0; //set all hotal to not visited
                }
                knapsack(current_num_hotels, budget, hotel_price, hotel_rating, hotel_name, selected);
                free(selected);
            }

            break;
        
        case 7:
            addPathToHotels(current_num_hotels, hotel_name, hotel_paths);

            break;
        
        case 8:
            findShortestPath(current_num_hotels, hotel_name, hotel_paths);

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