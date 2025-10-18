#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
    int id;
    char name[100];
    int age;
    char disease[100];
    struct Patient* next;
} Patient;

Patient* head = NULL;

Patient* createPatient(int id, char name[], int age, char disease[]) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->disease, disease);
    newPatient->next = NULL;
    return newPatient;
}

void addPatient(int id, char name[], int age, char disease[]) {
    Patient* newPatient = createPatient(id, name, age, disease);
    if (head == NULL) {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }
    printf("Patient added successfully.\n");
}

void displayPatients() {
    if (head == NULL) {
        printf("No patient records found.\n");
        return;
    }
    Patient* temp = head;
    printf("Patient Records:\n");
    while (temp != NULL) {
        printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n\n",
               temp->id, temp->name, temp->age, temp->disease);
        temp = temp->next;
    }
}

void searchPatient(int id) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Patient found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n",
                   temp->id, temp->name, temp->age, temp->disease);
            return;
        }
        temp = temp->next;
    }
    printf("Patient with ID %d not found.\n", id);
}

void deletePatient(int id) {
    Patient* temp = head;
    Patient* prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Patient with ID %d deleted successfully.\n", id);
}

int main() {
    int choice, id, age;
    char name[100], disease[100];

    while (1) {
        printf("\nHospital Patient Record System\n");
        printf("1. Add Patient\n2. Display All Patients\n3. Search Patient\n4. Delete Patient\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            return 1;
        }
        switch (choice) {
            case 1:
                printf("Enter patient ID: ");
                if (scanf("%d", &id) != 1) { fprintf(stderr, "Invalid ID.\n"); break; }
                printf("Enter patient name: ");
                scanf(" %[^\n]", name);     
                printf("Enter patient age: ");
                if (scanf("%d", &age) != 1) { fprintf(stderr, "Invalid age.\n"); break; }
                printf("Enter disease: ");
                scanf(" %[^\n]", disease);   
                addPatient(id, name, age, disease);
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                printf("Enter patient ID to search: ");
                if (scanf("%d", &id) != 1) { fprintf(stderr, "Invalid ID.\n"); break; }
                searchPatient(id);
                break;
            case 4:
                printf("Enter patient ID to delete: ");
                if (scanf("%d", &id) != 1) { fprintf(stderr, "Invalid ID.\n"); break; }
                deletePatient(id);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return 0;
}
