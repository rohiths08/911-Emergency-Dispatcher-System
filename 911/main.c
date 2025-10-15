#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cases {  // Doubly Linked List with priority
    int id;
    int pri;
    char loc[100], type[100];
    char department[100];
    struct cases *rptr, *lptr;
};
typedef struct cases cases;
cases* start = NULL;

// Global counters for departments and priorities
int next_id = 1;
int fire_count = 0, healthcare_count = 0, police_count = 0;
int high_priority = 0, moderate_priority = 0, low_priority = 0;

// Function to create a new case
cases* getcase() {
    cases *newcase;
    newcase = (cases*)malloc(sizeof(cases));
    newcase->id = next_id++;
    printf("\n911, What's the emergency? ");  // case type
    scanf("%s", newcase->type);
    printf("Please provide the address: ");  // location
    scanf("%s", newcase->loc);
    printf("Enter 1. High priority 2. Moderate 3. Low: ");
    scanf("%d", &newcase->pri);

    // Initialize department as empty
    newcase->department[0] = '\0';

    // Update priority counters
    if (newcase->pri == 1) high_priority++;
    else if (newcase->pri == 2) moderate_priority++;
    else if (newcase->pri == 3) low_priority++;

    newcase->rptr = newcase->lptr = NULL;
    return newcase;
}

// Function to assign cases to departments
void catrgory() {  // Sends details to particular services
    int flag;
    cases* temp = start;
    if (start == NULL) {
        printf("No cases to process.\n");
        return;
    }

    while (temp != NULL) {
        printf("\nProcessing case of type: %s\n", temp->type);
        printf("Location: %s\n", temp->loc);
        printf("Priority: %d\n", temp->pri);
        
        // Ask user for department assignment
        printf("Press the number corresponding to the required departments for this case:\n");
        printf("1. Fire Department\n");
        printf("2. Healthcare Department\n");
        printf("3. Police Department\n");
        printf("4. Send to all three departments (Fire, Healthcare, Police)\n");
        printf("5. Send to Fire & Healthcare\n");
        printf("6. Send to Fire & Police\n");
        printf("7. Send to Healthcare & Police\n");
        printf("8. None of the departments (false alarm)\n");
        printf("Enter your choice: ");
        scanf("%d", &flag);

        // Assign the case based on user choice
        switch (flag) {
            case 1:
                fire_count++;
                printf("Case successfully sent to Fire Department.\n");
                break;
            case 2:
                healthcare_count++;
                printf("Case successfully sent to Healthcare Department.\n");
                break;
            case 3:
                police_count++;
                printf("Case successfully sent to Police Department.\n");
                break;
            case 4:
                fire_count++;
                healthcare_count++;
                police_count++;
                printf("Case successfully sent to all three departments.\n");
                break;
            case 5:
                fire_count++;
                healthcare_count++;
                printf("Case successfully sent to Fire and Healthcare Departments.\n");
                break;
            case 6:
                fire_count++;
                police_count++;
                printf("Case successfully sent to Fire and Police Departments.\n");
                break;
            case 7:
                healthcare_count++;
                police_count++;
                printf("Case successfully sent to Healthcare and Police Departments.\n");
                break;
            case 8:
                printf("False alarm, no departments needed.\n");
                break;
            default:
                printf("Invalid choice. No departments assigned.\n");
                break;
        }
        temp = temp->rptr;  // Move to the next case in the DLL
    }
}

// Function to display all cases
void display() {
    cases *temp = start;
    int ct = 0;
    if (start == NULL) {
        printf("No cases to display.\n");
        return;
    }
    printf("Contents of cases are:\n");
    printf("Type \t Location \t Priority\n");
    while (temp != NULL) {
        printf(" %s\t %s\t %d\n", temp->type, temp->loc, temp->pri);
        temp = temp->rptr;
        ct++;
    }
    printf("No. of cases = %d\n", ct);
}

// Function to insert a new case at the rear (priority order)
void insert_rear(cases* new) {
    cases* temp = start;
    if (start == NULL) {
        start = new;
        return;
    }
    while (temp->rptr != NULL) temp = temp->rptr;
    temp->rptr = new;
    new->lptr = temp;
}

// Function to insert a new case at the front
void insert_front(cases* new) {
    cases *new1;
    new1 = getcase();
    if (start == NULL)
        start = new1;
    else {
        new1->rptr = start;
        start->lptr = new1;
        start = new1;
    }
}

// Function to receive case details and insert them
void call_info() {
    int p;
    printf("Enter 1. High priority 2. Moderate 3. Low: ");
    scanf("%d", &p);
    cases *new1;
    new1 = getcase();

    if (p >= new1->pri) {
        insert_rear(new1);
    } else
        insert_front(new1);
}

// Function to delete a case based on type
void search_del(char key) {
    cases* temp = start, * prev;
    while (key != temp->type) {
        prev = temp;
        temp = temp->rptr;
    }
    prev->rptr = temp->rptr;  // Link previous node to next node of temp
    printf("Deleted case %s\n", temp->type);
    free(temp);
}

// Function to display department and priority statistics
void display_statistics() {
    printf("\nDepartment Assignment Statistics:\n");
    printf("Fire Department: %d cases\n", fire_count);
    printf("Healthcare Department: %d cases\n", healthcare_count);
    printf("Police Department: %d cases\n", police_count);

    printf("\nPriority Level Statistics:\n");
    printf("High Priority: %d cases\n", high_priority);
    printf("Moderate Priority: %d cases\n", moderate_priority);
    printf("Low Priority: %d cases\n", low_priority);
}

// Function to search for cases by type or location
void search_cases(char query[]) {
    cases *temp = start;
    int found = 0;
    printf("\nSearch Results for '%s':\n", query);
    while (temp != NULL) {
        if (strstr(temp->type, query) != NULL || strstr(temp->loc, query) != NULL) {
            printf("Type: %s, Location: %s, Priority: %d\n", temp->type, temp->loc, temp->pri);
            found = 1;
        }
        temp = temp->rptr;
    }
    if (!found) {
        printf("No cases found matching the search query.\n");
    }
}

// ============================================================
// PYTHON LIBRARY FUNCTIONS (for ctypes integration)
// ============================================================

// Create a case programmatically (for Python)
cases* create_case(const char* case_type, const char* location, int priority, const char* department) {
    cases *newcase = (cases*)malloc(sizeof(cases));
    if (newcase == NULL) return NULL;
    
    newcase->id = next_id++;
    newcase->pri = priority;
    strncpy(newcase->type, case_type, sizeof(newcase->type) - 1);
    newcase->type[sizeof(newcase->type) - 1] = '\0';
    strncpy(newcase->loc, location, sizeof(newcase->loc) - 1);
    newcase->loc[sizeof(newcase->loc) - 1] = '\0';
    
    if (department != NULL) {
        strncpy(newcase->department, department, sizeof(newcase->department) - 1);
        newcase->department[sizeof(newcase->department) - 1] = '\0';
    } else {
        newcase->department[0] = '\0';
    }
    
    newcase->rptr = newcase->lptr = NULL;
    
    // Update priority counters
    if (priority == 1) high_priority++;
    else if (priority == 2) moderate_priority++;
    else if (priority == 3) low_priority++;
    
    return newcase;
}

// Add a new case (public API for Python)
int add_case(const char* case_type, const char* location, int priority, const char* department) {
    cases* newcase = create_case(case_type, location, priority, department);
    if (newcase == NULL) return -1;
    
    insert_rear(newcase);
    return newcase->id;
}

// Get case count
int get_case_count() {
    int count = 0;
    cases* temp = start;
    while (temp != NULL) {
        count++;
        temp = temp->rptr;
    }
    return count;
}

// Get case by ID
cases* get_case_by_id(int id) {
    cases* temp = start;
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->rptr;
    }
    return NULL;
}

// Delete case by ID (for Python)
int delete_case(int id) {
    cases* temp = start;
    
    while (temp != NULL && temp->id != id) {
        temp = temp->rptr;
    }
    
    if (temp == NULL) return 0; // Not found
    
    // Update priority counters
    if (temp->pri == 1) high_priority--;
    else if (temp->pri == 2) moderate_priority--;
    else if (temp->pri == 3) low_priority--;
    
    // Remove from list
    if (temp->lptr != NULL) {
        temp->lptr->rptr = temp->rptr;
    } else {
        start = temp->rptr;
    }
    
    if (temp->rptr != NULL) {
        temp->rptr->lptr = temp->lptr;
    }
    
    free(temp);
    return 1; // Success
}

// Assign department to a case
int assign_department(int id, const char* department) {
    cases* temp = get_case_by_id(id);
    if (temp == NULL) return 0;
    
    // Remove old department count
    if (strstr(temp->department, "Fire") != NULL) fire_count--;
    if (strstr(temp->department, "Healthcare") != NULL) healthcare_count--;
    if (strstr(temp->department, "Police") != NULL) police_count--;
    
    // Update department
    strncpy(temp->department, department, sizeof(temp->department) - 1);
    temp->department[sizeof(temp->department) - 1] = '\0';
    
    // Update department counters
    if (strstr(department, "Fire") != NULL) fire_count++;
    if (strstr(department, "Healthcare") != NULL) healthcare_count++;
    if (strstr(department, "Police") != NULL) police_count++;
    
    return 1;
}

// Get all cases (for Python to parse)
int get_all_cases(int* ids, char* types, char* locations, int* priorities, char* departments, int max_cases) {
    cases* temp = start;
    int count = 0;
    
    while (temp != NULL && count < max_cases) {
        ids[count] = temp->id;
        priorities[count] = temp->pri;
        
        // Copy strings with proper offsets
        strncpy(types + (count * 100), temp->type, 99);
        types[(count * 100) + 99] = '\0';
        
        strncpy(locations + (count * 100), temp->loc, 99);
        locations[(count * 100) + 99] = '\0';
        
        strncpy(departments + (count * 100), temp->department, 99);
        departments[(count * 100) + 99] = '\0';
        
        count++;
        temp = temp->rptr;
    }
    
    return count;
}

// Get statistics (for Python)
void get_statistics(int* stats) {
    stats[0] = fire_count;
    stats[1] = healthcare_count;
    stats[2] = police_count;
    stats[3] = high_priority;
    stats[4] = moderate_priority;
    stats[5] = low_priority;
}

// Search cases by query (for Python)
int search_cases_by_query(const char* query, int* result_ids, int max_results) {
    cases* temp = start;
    int count = 0;
    
    while (temp != NULL && count < max_results) {
        if (strstr(temp->type, query) != NULL || strstr(temp->loc, query) != NULL) {
            result_ids[count++] = temp->id;
        }
        temp = temp->rptr;
    }
    
    return count;
}

// Clear all cases
void clear_all_cases() {
    cases* temp = start;
    cases* next;
    
    while (temp != NULL) {
        next = temp->rptr;
        free(temp);
        temp = next;
    }
    
    start = NULL;
    fire_count = healthcare_count = police_count = 0;
    high_priority = moderate_priority = low_priority = 0;
    next_id = 1;
}

// ============================================================
// ORIGINAL CLI MAIN FUNCTION
// ============================================================

// Main function
void main() {
    int ch;
    char key[20], search_query[50];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Answer the call\n");
        printf("2. Display all cases\n");
        printf("3. Mark cases closed\n");
        printf("4. Assign cases to departments\n");
        printf("5. Display department statistics\n");
        printf("6. Search cases\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1:
                call_info();  // New case entry
                break;
            case 2:
                display();  // Show all cases
                break;
            case 3:
                printf("Enter the case type to delete: ");
                scanf("%s", key);
                search_del(key);  // Delete case by type
                break;
            case 4:
                catrgory();  // Assign cases to departments
                break;
            case 5:
                display_statistics();  // Show department and priority statistics
                break;
            case 6:
                printf("Enter search query: ");
                scanf("%s", search_query);  // Search for cases
                search_cases(search_query);
                break;
            case 7:
                return;  // Exit program
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}
