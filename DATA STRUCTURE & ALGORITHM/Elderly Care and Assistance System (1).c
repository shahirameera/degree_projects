#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

struct details // define struct for person details
{
	char name[150]; 
	int age;
	char disease[50];
	char phoneNum[20];
	char dob[20];  // Date of Birth
    char address[200];  // Address
    char emergencyContact[30];
    char identityCardNum[30];

};
struct Activity // define struct for activity
{
	char personName[150];
    char activityName[150];
    int timeOfDay;
    struct Activity* next;
};

struct medication //define struct for medication
{
    char personName[150];
    char medicine[50];
    float timeOfDay;
    int timesPerDay, timesTaken;

};

struct MedicationStack 
{
    struct medication data;
    struct MedicationStack* next;
};

struct person
{
	struct details data;
	struct person * ptrnext;
	struct MedicationStack* medicationStack;
};

struct person *headptr,*newptr,*curptr,*prevptr;

struct Activity* front = NULL;
struct Activity* rear = NULL;

struct person *merge(struct person *left, struct person *right);
struct person *mergeSort(struct person *head);

void insertDataFromUser();
void displayData(struct person *start);
void updatePersonDetail(char name[]);
void searchByName(const char *targetName);
void searchByDisease(const char *targetDisease);
void deletePerson(char name[]);
void addMedication(struct person* personPtr);
void displayMedicationsByName(struct person* personPtr);
void markMedicationTaken(struct person* personPtr);
void scheduleActivity(char name[]);
void dequeueActivity();
void displayActivities();
void bubbleSort() ;



int main()
{
	 // Initialize the head pointer to NULL
    headptr = NULL;

    int choice;
    char addMore;


	do
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t WELCOME TO OUR ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		printf("\t\t\t\t----------------------------------------------------\n");
		printf("\n");
		printf("\t\t\t                           [MAIN MENU]");
		printf("\n\n");
		printf("\n\t\t               [1] Add Person Details ");
		printf("\n\t\t               [2] Update Person Details ");
		printf("\n\t\t               [3] Display Person Details ");
		printf("\n\t\t               [4] Search by Person ");
		printf("\n\t\t               [5] Search by Diesease");
		printf("\n\t\t               [6] Delete Person Details ");
		printf("\n\t\t               [7] Add Medication for Person ");
		printf("\n\t\t               [8] Display current Medication  ");
		printf("\n\t\t               [9] Taken Medication ");
		printf("\n\t\t               [10] Schedule Activities ");
		printf("\n\t\t               [11] Display Activities ");
		printf("\n\t\t               [12] Remove Activities ");
		printf("\n\t\t               [13] Sort Person by age ");
		printf("\n\t\t               [14] Sort Person by alphabet ");
		printf("\n\t\t               [15] Exit ");
		
		printf("\n\t\t               Enter Your Choice: ");
		scanf("%d",&choice);
		
		switch (choice) {
            case 1:
                // Insert data
                system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
	         	printf("\t\t\t\t          -----------------------------------------\n");
                printf("\n\t\t               PLEASE FILL UP THE PERSON DETAILS BELOW: ");
                printf("\n\n");
                insertDataFromUser();
                break;
            case 2:
               // Update person details
               system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
               if (headptr != NULL) 
			   {
                char nameToUpdate[150];
                printf("\n\t\t               Enter the name of the person to update: ");
                getchar(); // consume the newline character left in the buffer
                fgets(nameToUpdate, sizeof(nameToUpdate), stdin);
                strtok(nameToUpdate, "\n");  // remove newline character
                updatePersonDetail(nameToUpdate);
				} 
				else
				{
                printf("\n\t\t               No data to update. Please insert data first.\n");
                }
                break;
            case 3:
                // Display all person details
                system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
                if (headptr != NULL) {
                    displayData(headptr);
                } else {
                    printf("\n\t\t               No data to display. Please insert data first.\n");
                }
                break;
            case 4:
            	system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	printf("\n\t\t               Enter the person's name to search: ");
                char searchName[150];
                getchar();
                fgets(searchName, sizeof(searchName), stdin);
                strtok(searchName, "\n");
                searchByName(searchName);
            	break;
            case 5:
            	system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	printf("\n\t\t               Enter the disease to search (Dementia, Diabetes, Stroke, Hypertension, Alzheimer): ");
                char searchDisease[50];
                getchar();
                fgets(searchDisease, sizeof(searchDisease), stdin);
                strtok(searchDisease, "\n");
                searchByDisease(searchDisease);
            	break;
            case 6:
                // Delete person details
                system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
                if (headptr != NULL) {
                    char nameToDelete[150];
                    printf("\n\t\t               Enter the name of the person to delete: ");
                    getchar(); // consume the newline character left in the buffer
                    fgets(nameToDelete, sizeof(nameToDelete), stdin);
                    strtok(nameToDelete, "\n");  // remove newline character
                    deletePerson(nameToDelete);
                } else {
                    printf("\n\t\t               No data to delete. Please insert data first.\n");
                }
                break;
            case 7:
            	system("cls");
                printf("\n\n\n");
                printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
                printf("\t\t\t\t          -----------------------------------------\n");
                if (headptr != NULL) {
                    char nameToAddMedication[150];
                    printf("\n\t\t               Enter the name of the person to add medication: ");
                    getchar(); // consume the newline character left in the buffer
                    fgets(nameToAddMedication, sizeof(nameToAddMedication), stdin);
                    strtok(nameToAddMedication, "\n");  // remove newline character

                    curptr = headptr;
                    while (curptr != NULL && strcmp(curptr->data.name, nameToAddMedication) != 0) {
                        curptr = curptr->ptrnext;
                    }

                    if (curptr != NULL) {
                        addMedication(curptr);
                    } else {
                        printf("\n\t\t               Person with name %s not found.\n", nameToAddMedication);
                    }
                } else {
                    printf("\n\t\t               No data to add medication. Please insert data first.\n");
                }
            	break;
            case 8:
            	system("cls");
                printf("\n\n\n");
                printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
                printf("\t\t\t\t          -----------------------------------------\n");
                if (headptr != NULL) 
				{
                    char nameToDisplayMedications[150];
                    printf("\n\t\t               Enter the name of the person to display medications: ");
                    getchar(); // consume the newline character left in the buffer
                    fgets(nameToDisplayMedications, sizeof(nameToDisplayMedications), stdin);
                    strtok(nameToDisplayMedications, "\n");  // remove newline character

                    curptr = headptr;
                    while (curptr != NULL && strcmp(curptr->data.name, nameToDisplayMedications) != 0) {
                        curptr = curptr->ptrnext;
                    }

                    if (curptr != NULL) {
                        displayMedicationsByName(curptr);
                    } else {
                        printf("\n\t\t               Person with name %s not found.\n", nameToDisplayMedications);
                    }
                } else {
                    printf("\n\t\t               No data to display medications. Please insert data first.\n");
                }
            	break;
            case 9:
            	system("cls");
                printf("\n\n\n");
                printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
                printf("\t\t\t\t          -----------------------------------------\n");
                if (headptr != NULL) {
                    char nameToMarkMedication[150];
                    printf("\n\t\t               Enter the name of the person to mark medication as taken: ");
                    getchar(); // consume the newline character left in the buffer
                    fgets(nameToMarkMedication, sizeof(nameToMarkMedication), stdin);
                    strtok(nameToMarkMedication, "\n");  // remove newline character

                    curptr = headptr;
                    while (curptr != NULL && strcmp(curptr->data.name, nameToMarkMedication) != 0) {
                        curptr = curptr->ptrnext;
                    }

                    if (curptr != NULL) {
                        markMedicationTaken(curptr);
                    } else {
                        printf("\n\t\t               Person with name %s not found.\n", nameToMarkMedication);
                    }
                } else {
                    printf("\n\t\t               No data to mark medication as taken. Please insert data first.\n");
                }
            	break;
            case 10:
                // Scheduling activities
                system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	if (headptr != NULL) 
            	{
            		char nametoSchedule[150];
            		printf("\n\t\t               Enter person's name: ");
            		getchar();
                    fgets(nametoSchedule, sizeof(nametoSchedule), stdin);
                    strtok(nametoSchedule, "\n"); 
                    scheduleActivity(nametoSchedule);
                }
            	else 
				{
                    printf("\n\t\t               No data to schedule activity. Please insert data first.\n");
                }
                break;
            case 11:
            	system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	displayActivities();
                break;
            case 12:
            	system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	dequeueActivity();
                break;
            case 13:
            	system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
            	bubbleSort();
            	break;
			case 14:
				system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
		        printf("\n\t\t               Sort Person by alphabet ");
                printf("\n\n");
                
                 if (headptr != NULL)
				{
                    headptr = mergeSort(headptr);
                    displayData(headptr);
                } else {
                    printf("\n\t\t               No data to sort. Please insert data first.\n");
                }
                break;
            case 15:
                system("cls");
               	printf("\n\n\n");
		        printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		        printf("\t\t\t\t          -----------------------------------------\n");
			    printf("\n\n\t\t\t\t            Thank You For using our system !! ");
			    printf("\n\n\n");
			    exit(0);
                break;
            default:
                printf("\n\t\t               Invalid choice\n");
                break;
        }
        
        // Ask the user if they want to continue
        if (choice != 15) {
            printf("\n\t\t               Do you want to perform another operation? (y/n): ");
            scanf(" %c", &addMore);  // note the space before %c to consume the newline character
            getchar();  // consume the newline character left in the buffer
        }

    } while (choice != 15 && (addMore == 'y' || addMore == 'Y'));
		
	
		if(addMore=='N'||addMore=='n')
		{
			system("cls");
            printf("\n\n\n");
		    printf("\t\t\t\t             ELDERLY CARE AND ASSISTANCE SYSTEM \n");
		    printf("\t\t\t\t          -----------------------------------------\n");
			printf("\n\n\t\t\t\t             Thank You For using our system !! ");
			printf("\n\n\n");
			exit(0);
		}
		
	// Clean up: free allocated memory (you may want to do this in a separate function)
    curptr = headptr;
    while (curptr != NULL) {
        prevptr = curptr;
        curptr = curptr->ptrnext;
        free(prevptr);
    }
	
return 0;
}

// Function to insert a new node with user-input data

void insertDataFromUser() 
{
    newptr = (struct person *)malloc(sizeof(struct person));
    if (newptr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("\n\t\t               Enter name: ");
    getchar();
    fgets(newptr->data.name, sizeof(newptr->data.name), stdin);
    strtok(newptr->data.name, "\n");

    printf("\n\t\t               Enter age: ");
    scanf("%d", &newptr->data.age);

    printf("\n\t\t               Enter disease (Dementia, Diabetes, Stroke, Hypertension, Alzheimer): ");
    getchar();
    fgets(newptr->data.disease, sizeof(newptr->data.disease), stdin);
    strtok(newptr->data.disease, "\n");

    printf("\n\t\t               Enter phone number: ");
    fgets(newptr->data.phoneNum, sizeof(newptr->data.phoneNum), stdin);
    strtok(newptr->data.phoneNum, "\n");

    printf("\n\t\t               Enter Date of Birth (MM/DD/YYYY): ");
    fgets(newptr->data.dob, sizeof(newptr->data.dob), stdin);
    strtok(newptr->data.dob, "\n");

    printf("\n\t\t               Enter address: ");
    fgets(newptr->data.address, sizeof(newptr->data.address), stdin);
    strtok(newptr->data.address, "\n");

    printf("\n\t\t               Enter emergency contact: ");
    fgets(newptr->data.emergencyContact, sizeof(newptr->data.emergencyContact), stdin);
    strtok(newptr->data.emergencyContact, "\n");

    printf("\n\t\t               Enter identity card number: ");
    fgets(newptr->data.identityCardNum, sizeof(newptr->data.identityCardNum), stdin);
    strtok(newptr->data.identityCardNum, "\n");
    
    newptr->medicationStack = NULL;

    newptr->ptrnext = headptr;
    headptr = newptr;
}


// Function to display data of each person in the linked list
void displayData(struct person *start)
{
    curptr = start;

    // Traverse the linked list and print each person's data
    while (curptr != NULL) {
        printf("\n\t\t               Name: %s\n", curptr->data.name);
        printf("\n\t\t               Age: %d\n", curptr->data.age);
        printf("\n\t\t               Date of Birth: %s\n", curptr->data.dob);
        printf("\n\t\t               Address: %s\n", curptr->data.address);
        printf("\n\t\t               Disease: %s\n", curptr->data.disease);
        printf("\n\t\t               Phone Number: %s\n", curptr->data.phoneNum);
        printf("\n\t\t               Emergency Contact: %s\n", curptr->data.emergencyContact);
        printf("\n\t\t               Identity Card Number: %s\n", curptr->data.identityCardNum);
        printf("\n");

        curptr = curptr->ptrnext;
    }
}


// Function to update a specific detail of a person based on their name
void updatePersonDetail(char name[]) 
{
    curptr = headptr;

    // Traverse the linked list to find the person with the specified name
    while (curptr != NULL && strcmp(curptr->data.name, name) != 0) {
        prevptr = curptr;
        curptr = curptr->ptrnext;
    }

    if (curptr != NULL) {
        // Person found, ask the user which detail to update
        printf("\n\t\t               Choose which detail to update:\n");
        printf("\n\t\t               1. Disease\n");
        printf("\n\t\t               2. Address\n");
        printf("\n\t\t               3. Emergency Contact\n");
        printf("\n\t\t               Enter your choice (1-3): ");

        int detailChoice;
        scanf("%d", &detailChoice);

        // Consume the newline character in the buffer
        getchar();

        switch (detailChoice) {
            case 1:
                // Update disease
                printf("\n\t\t               Enter new disease: ");
                fgets(curptr->data.disease, sizeof(curptr->data.disease), stdin);
                strtok(curptr->data.disease, "\n");
                break;
            case 2:
                // Update address
                printf("\n\t\t               Enter new Address: ");
                fgets(curptr->data.address, sizeof(curptr->data.address), stdin);
                strtok(curptr->data.address, "\n");
                break;
            case 3:
                // Update emergency contact
                printf("\n\t\t               Enter new emergency contact: ");
                fgets(curptr->data.emergencyContact, sizeof(curptr->data.emergencyContact), stdin);
                strtok(curptr->data.emergencyContact, "\n");
                break;
            default:
                printf("\n\t\t               Invalid choice. No details updated.\n");
                return;
        }

        printf("\n\t\t               Person details updated successfully!\n");
    } else {
        printf("\n\t\t               Person not found.\n");
    }
}


void searchByName(const char *targetName) 
{
    curptr = headptr;
    int found = 0;

    while (curptr != NULL) {
        if (strcmp(curptr->data.name, targetName) == 0) {
            found = 1;
            break;
        }
        curptr = curptr->ptrnext;
    }

    if (found) {
        printf("\n\t\t               Person found!\n");
        printf("\n\t\t               Name: %s\n", curptr->data.name);
        printf("\n\t\t               Age: %d\n", curptr->data.age);
        printf("\n\t\t               Disease: %s\n", curptr->data.disease);
        printf("\n\t\t               Phone Number: %s\n", curptr->data.phoneNum);
    } else {
        printf("\n\t\t               Person not found.\n");
    }
}

void searchByDisease(const char *targetDisease) 
{
    curptr = headptr;
    int found = 0;

    while (curptr != NULL) {
        if (strcmp(curptr->data.disease, targetDisease) == 0) {
            found = 1;
            break;
        }
        curptr = curptr->ptrnext;
    }

    if (found) {
        printf("\n\t\t               Person found!\n");
        printf("\n\t\t               Name: %s\n", curptr->data.name);
        printf("\n\t\t               Age: %d\n", curptr->data.age);
        printf("\n\t\t               Disease: %s\n", curptr->data.disease);
        printf("\n\t\t               Phone Number: %s\n", curptr->data.phoneNum);
    } else {
        printf("\n\t\t               Person not found.\n");
    }
}

void deletePerson(char name[]) 
{
    curptr = headptr;
    struct person *temp;

    // Special case: deleting the head node
    if (curptr != NULL && strcmp(curptr->data.name, name) == 0) {
        headptr = curptr->ptrnext;
        free(curptr);
        printf("\n\t\t               Person details deleted successfully!\n");
        return;
    }

    // Search for the person to delete
    while (curptr != NULL && strcmp(curptr->data.name, name) != 0) {
        prevptr = curptr;
        curptr = curptr->ptrnext;
    }

    // If the person is found, delete them
    if (curptr != NULL) {
        prevptr->ptrnext = curptr->ptrnext;
        free(curptr);
        printf("\n\t\t               Person details deleted successfully!\n");
    } else {
        printf("\n\t\t               Person not found.\n");
    }
}

// Function to display data of all persons in the linked list
void displaydetails() 
{
    printf("\n\t\t               Displaying data of all persons:\n");
    displayData(headptr);
}

// Modify the function definition for the addMedication function
void addMedication(struct person* personPtr) 
{
    struct medication newMedication;
    printf("\n\t\t               Enter medicine name: ");
    getchar(); // consume the newline character left in the buffer
    fgets(newMedication.medicine, sizeof(newMedication.medicine), stdin);
    strtok(newMedication.medicine, "\n");

    printf("\n\t\t               Enter times per day: ");
    scanf("%d", &newMedication.timesPerDay);

    if (newMedication.timesPerDay > 1)
	 {
        for (int i = 0; i < newMedication.timesPerDay; ++i) {
            printf("\n\t\t               Enter time to take the medicine for instance %d (1 for Morning, 2 for Afternoon, 3 for Evening): ", i + 1);
            scanf("%d", &newMedication.timeOfDay);

            // Create a new node for the medication
            struct MedicationStack* newNode = (struct MedicationStack*)malloc(sizeof(struct MedicationStack));

            if (newNode == NULL) {
                printf("\n\n\t\t               Memory allocation failed!\n");
                exit(1);
            }

            newNode->data = newMedication;
            newNode->next = personPtr->medicationStack;
            personPtr->medicationStack = newNode;
        }
    } else {
        printf("\n\t\t               Enter time to take the medicine (1 for Morning, 2 for Afternoon, 3 for Evening): ");
        scanf("%d", &newMedication.timeOfDay);

        // Create a new node for the medication
        struct MedicationStack* newNode = (struct MedicationStack*)malloc(sizeof(struct MedicationStack));

        if (newNode == NULL) {
            printf("\n\n\t\t               Memory allocation failed!\n");
            exit(1);
        }

        newNode->data = newMedication;
        newNode->next = personPtr->medicationStack;
        personPtr->medicationStack = newNode;
    }

    printf("\n\t\t               Medication information added successfully for %s!\n", personPtr->data.name);
}

void displayMedicationsByName(struct person* personPtr) 
{
    if (personPtr->medicationStack == NULL) 
	{
        printf("\n\t\t               No medications for %s.\n", personPtr->data.name);
        return;
    }

    printf("\n\t\t               Medications for %s:\n", personPtr->data.name);

    struct MedicationStack* currentMedication = personPtr->medicationStack;
    int count = 1;

    while (currentMedication != NULL) {
        printf("\n\t\t               %d. Medicine: %s\n", count, currentMedication->data.medicine);
        printf("\t\t                  Times Per Day: %d\n", currentMedication->data.timesPerDay);

        currentMedication = currentMedication->next;
        count++;  // Increment count for the next medication
    }
}


void markMedicationTaken(struct person* personPtr)
{
    if (personPtr->medicationStack == NULL) {
        printf("\n\t\t               No medications to mark as taken for %s.\n", personPtr->data.name);
        return;
    }

    printf("\n\t\t               Medications for %s:\n", personPtr->data.name);

    struct MedicationStack* currentMedication = personPtr->medicationStack;
    int count = 1;

    // Display medications and let the user choose which one to mark as taken
    while (currentMedication != NULL) {
        printf("\n\t\t               %d. Medicine: %s\n", count, currentMedication->data.medicine);
        printf("\t\t                  Times Per Day: %d\n", currentMedication->data.timesPerDay);
        printf("\t\t                  Time of Day: %d\n", currentMedication->data.timeOfDay);

        currentMedication = currentMedication->next;
        count++;
    }

    int choice;
    printf("\n\t\t               Enter the number of the medication to mark as taken: ");
    scanf("%d", &choice);

    // Remove the chosen medication node from the stack
    if (choice == 1) {
        // Special case if the first node is chosen
        struct MedicationStack* temp = personPtr->medicationStack;
        personPtr->medicationStack = temp->next;
        free(temp);
    } else {
        // General case for other nodes
        currentMedication = personPtr->medicationStack;
        for (int i = 1; i < choice - 1 && currentMedication->next != NULL; i++) {
            currentMedication = currentMedication->next;
        }

        if (currentMedication->next != NULL) {
            struct MedicationStack* temp = currentMedication->next;
            currentMedication->next = temp->next;
            free(temp);
        } else {
            printf("\n\t\t               Invalid choice. No medication removed.\n");
            return;
        }
    }

    printf("\n\t\t               Medication marked as taken for %s!\n", personPtr->data.name);
}


void scheduleActivity(char name[]) 
{
	curptr = headptr;
    int personFound = 0;

    while (curptr != NULL) {
        if (strcmp(curptr->data.name, name) == 0) {
            personFound = 1;
            break;
        }
        curptr = curptr->ptrnext;
    }

    if (!personFound) {
        printf("\n\t\t               Person with name %s not found in the system.\n", name);
        return;
    }

    struct Activity newActivity;
    strcpy(newActivity.personName, name);

    // Choose activity
    printf("\n\t\t               Choose activity (1 - Exercise Class, 2 - Art and Craft Session, 3 - Memory Games and Brain Exercises, 4 - Music Therapy and Sing-Alongs, 5 - Outdoor Garden Walks): ");
    int activityOption;
    scanf("%d", &activityOption);

    switch (activityOption) {
        case 1:
            strcpy(newActivity.activityName, "Exercise Class");
            break;
        case 2:
            strcpy(newActivity.activityName, "Art and Craft Session");
            break;
        case 3:
            strcpy(newActivity.activityName, "Memory Games and Brain Exercises");
            break;
        case 4:
            strcpy(newActivity.activityName, "Music Therapy and Sing-Alongs");
            break;
        case 5:
            strcpy(newActivity.activityName, "Outdoor Garden Walks");
            break;
        default:
            printf("\n\t\t               Invalid activity. Please select 1 to 5.\n");
            return;
    }

    // Choose time for the activity
    printf("\n\t\t               Choose time for the activity (1 for Morning, 2 for Afternoon, 3 for Evening): ");
    scanf("%d", &newActivity.timeOfDay);

    if (newActivity.timeOfDay < 1 || newActivity.timeOfDay > 3) {
        printf("\n\t\t               Invalid time. Please select 1, 2, or 3.\n");
        return;
    }

    printf("\n\t\t               Activity scheduled successfully for ");

    switch (newActivity.timeOfDay) {
        case 1:
            printf("Morning");
            break;
        case 2:
            printf("Afternoon");
            break;
        case 3:
            printf("Evening");
            break;
    }

    printf("!\n");

    // Create a new node for the activity
    struct Activity* newNode = (struct Activity*)malloc(sizeof(struct Activity));

    if (newNode == NULL) {
        printf("\n\n\t\t               Memory allocation failed!\n");
        return;
    }

    strcpy(newNode->personName, newActivity.personName);
    strcpy(newNode->activityName, newActivity.activityName);
    newNode->timeOfDay = newActivity.timeOfDay;
    newNode->next = NULL;

    // Add the new node to the linked list
    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    // Display the updated list of activities
    displayActivities();
}

void dequeueActivity()
{
    if (front == NULL) {
        printf("\n\n\t\t               !!! Activity Queue is EMPTY - Cannot dequeue !!!\n");
    } else {
        struct Activity* temp = front;
        front = front->next;
        free(temp);
        printf("\n\n\t\t               Front activity dequeued successfully!\n");
    }

    displayActivities();
}

void displayActivities() 
{
    if (front == NULL) {
        printf("\n\n\t\t               The activity queue is empty\n");
    } else {
        struct Activity* current = front;

        printf("\n\n\t\t               Scheduled Activities:\n");
        printf("\n\t\t                 Time of Day (1.Morining, 2.Afternoon, 3.Evening)\n");
        while (current != NULL) {
            printf("\n\t\t               Person: %s, Activity: %s, Time of Day: %d\n", current->personName, current->activityName, current->timeOfDay);
            current = current->next;
        }
    }
}

void bubbleSort() 
{
    if (headptr == NULL || headptr->ptrnext == NULL) {
        // No need to sort if the list is empty or has only one element
        return;
    }

    int swapped;
    struct person *last = NULL;

    do {
        swapped = 0;
        curptr = headptr;

        while (curptr->ptrnext != last) {
            if (curptr->data.age > curptr->ptrnext->data.age) {
                // Swap nodes
                struct person *temp = curptr->ptrnext;
                curptr->ptrnext = temp->ptrnext;
                temp->ptrnext = curptr;
                if (curptr == headptr) {
                    headptr = temp;
                } else {
                    prevptr->ptrnext = temp;
                }
                swapped = 1;
            } else {
                prevptr = curptr;
                curptr = curptr->ptrnext;
            }
        }

        last = curptr;

    } while (swapped);
    
    displaydetails();
}

// Merge Sort function for sorting by name alphabetically
struct person *merge(struct person *left, struct person *right) 
{
    struct person *result = NULL;

    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (strcmp(left->data.name, right->data.name) <= 0) {
        result = left;
        result->ptrnext = merge(left->ptrnext, right);
    } else {
        result = right;
        result->ptrnext = merge(left, right->ptrnext);
    }

    return result;
}

struct person *mergeSort(struct person *head) 
{
    if (head == NULL || head->ptrnext == NULL) {
        return head;
    }

    struct person *slow = head;
    struct person *fast = head->ptrnext;

    while (fast != NULL && fast->ptrnext != NULL) {
        slow = slow->ptrnext;
        fast = fast->ptrnext->ptrnext;
    }

    struct person *left = head;
    struct person *right = slow->ptrnext;
    slow->ptrnext = NULL;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
    
    displaydetails();
}