#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cases {  // Doubly Linked List with priority
    int pri;
    char loc[50], type[50];
    struct cases *rptr, *lptr;
};
typedef struct cases cases;
cases* start = NULL;

// Global counters for departments and priorities
int fire_count = 0, healthcare_count = 0, police_count = 0;
int high_priority = 0, moderate_priority = 0, low_priority = 0;

// Function to create a new case
cases* getcase() {
    cases *newcase;
    newcase = (cases*)malloc(sizeof(cases));
    printf("\n911, What's the emergency? ");  // case type
    scanf("%s", newcase->type);
    printf("Please provide the address: ");  // location
    scanf("%s", newcase->loc);
    printf("Enter 1. High priority 2. Moderate 3. Low: ");
    scanf("%d", &newcase->pri);

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
