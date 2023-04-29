#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPERTS 100

struct Expert {
    int id;
    char name[50];
    char expertise[50];
    char contact[20];
};

int i;
void addExpert(struct Expert experts[], int *numExperts){
    if (*numExperts >= MAX_EXPERTS) {
        printf("Maximum number of experts reached.\n");
        return;
    }
    
    struct Expert expert;
    expert.id = *numExperts + 1;
    printf("Enter expert name: ");
    scanf("%s", expert.name);
    printf("Enter expertise: ");
    scanf("%s", expert.expertise);
    printf("Enter contact number: ");
    scanf("%s", expert.contact);
    
    experts[*numExperts] = expert;
    *numExperts += 1;
    
    printf("Expert added successfully.\n");
}

void displayExperts(struct Expert experts[], int numExperts) {
    printf("ID\tName\tExpertise\tContact\n");
    for (i = 0; i < numExperts; i++) {
        printf("%d\t%s\t%s\t%s\n", experts[i].id, experts[i].name, experts[i].expertise, experts[i].contact);
    }
}

void searchExpert(struct Expert experts[], int numExperts) {
    int id;
    printf("Enter expert ID: ");
    scanf("%d", &id);
    
    for (i = 0; i < numExperts; i++) {
        if (experts[i].id == id) {
            printf("Expert details:\n");
            printf("Name: %s\n", experts[i].name);
            printf("Expertise: %s\n", experts[i].expertise);
            printf("Contact: %s\n", experts[i].contact);
            return;
        }
    }
    
    printf("Expert not found.\n");
}

void saveExpertsToFile(struct Expert experts[], int numExperts) {
    FILE *fp;
    fp = fopen("experts.txt", "w");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    
    for (i = 0; i < numExperts; i++) {
        fprintf(fp, "%d,%s,%s,%s\n", experts[i].id, experts[i].name, experts[i].expertise, experts[i].contact);
    }
    
    fclose(fp);
    printf("Experts saved to file.\n");
}

void loadExpertsFromFile(struct Expert experts[], int *numExperts) {
    FILE *fp;
    fp = fopen("experts.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    
    int id;
    char name[50], expertise[50], contact[20];
    while (fscanf(fp, "%d,%[^,],%[^,],%s\n", &id, name, expertise, contact) == 4) {
        struct Expert expert;
        expert.id = id;
        strcpy(expert.name, name);
        strcpy(expert.expertise, expertise);
        strcpy(expert.contact, contact);
        
        experts[*numExperts] = expert;
        *numExperts += 1;
    }
    
    fclose(fp);
    printf("Experts loaded from file.\n");
}
int main() {
    struct Expert experts[MAX_EXPERTS];
    int numExperts = 0;
    
    int choice;
    do {
        printf("Laptop Repair System - Expert Details\n");
        printf("1. Add Expert\n");
        printf("2. Display Experts\n");
        printf("3. Search Expert\n");
        printf("4. Save Experts to File\n");
        printf("5. Load Experts from File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addExpert(experts, &numExperts);
                break;
            case 2:
                displayExperts(experts, numExperts);
                break;
            case 3:
                searchExpert(experts, numExperts);
                break;
            case 4:
                saveExpertsToFile(experts, numExperts);
                break;
            case 5:
                loadExpertsFromFile(experts, &numExperts);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}
