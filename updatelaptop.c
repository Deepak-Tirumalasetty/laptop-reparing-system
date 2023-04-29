#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LAPTOPS 50

typedef struct {
    char brand[20];
    char model[20];
    int serial_number;
    char problem[100];
} laptop;

int i, num_laptops = 0;
laptop laptops[MAX_LAPTOPS];

void add_laptop() {
    if (num_laptops == MAX_LAPTOPS) {
        printf("Error: Maximum number of laptops reached.\n");
        return;
    }
    laptop new_laptop;
    printf("Enter brand: ");
    scanf("%s", new_laptop.brand);
    printf("Enter model: ");
    scanf("%s", new_laptop.model);
    printf("Enter serial number: ");
    scanf("%d", &new_laptop.serial_number);
    printf("Enter problem description: ");
    scanf("%s", new_laptop.problem);

    laptops[num_laptops++] = new_laptop;
    printf("Laptop added successfully.\n");

    FILE *file = fopen("laptops.txt", "a");
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    fprintf(file, "%s,%s,%d,%s\n", new_laptop.brand, new_laptop.model, new_laptop.serial_number, new_laptop.problem);
    fclose(file);
}

void display_laptops() {
    FILE *file = fopen("laptops.txt", "r");
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return;
    }
    printf("Laptop Details:\n");
    int laptop_count = 0;
    while (!feof(file)) {
        char brand[20], model[20], problem[100];
        int serial_number;
        fscanf(file, "%[^,],%[^,],%d,%[^,\n]\n", brand, model, &serial_number, problem);
        if (strlen(brand) > 0) {
            laptop_count++;
            printf("Laptop %d:\n", laptop_count);
            printf("Brand: %s\n", brand);
            printf("Model: %s\n", model);
            printf("Serial Number: %d\n", serial_number);
            printf("Problem: %s\n", problem);
        }
    }
    if (laptop_count == 0) {
        printf("No laptops added.\n");
    }
    fclose(file);
}

int main() {
    FILE *file = fopen("laptops.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            char brand[20], model[20], problem[100];
            int serial_number;
            fscanf(file, "%[^,],%[^,],%d,%[^,\n]\n", brand, model, &serial_number, problem);
            if (strlen(brand) > 0) {
                laptop new_laptop = {0};
                strcpy(new_laptop.brand, brand);
                strcpy(new_laptop.model, model);
                new_laptop.serial_number = serial_number;
                strcpy(new_laptop.problem, problem);
                laptops[num_laptops++] = new_laptop;
            }
        }
        fclose(file);
    }

    int choice;
    while (1) {
        printf("\n1. Add laptop details\n");
        printf("2. Display laptop details\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_laptop();
                break;
            case 2:
                display_laptops();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
	return 0;
}
