#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LAPTOPS 50

typedef struct laptop {
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
    scanf("%s", &new_laptop.brand);

    printf("Enter model: ");
    scanf("%s", &new_laptop.model);

    printf("Enter serial number: ");
    scanf("%d", &new_laptop.serial_number);

    printf("Enter problem description: ");
    scanf("%s", &new_laptop.problem);

    laptops[num_laptops++] = new_laptop;

    printf("Laptop added successfully.\n");
}

void display_laptops() {
    if (num_laptops == 0) {
        printf("No laptops added.\n");
        return;
    }

    printf("Laptop Details:\n");

    for (i = 0; i < num_laptops; i++) {
        printf("Laptop %d:\n", i+1);
        printf("Brand: %s\n", laptops[i].brand);
        printf("Model: %s\n", laptops[i].model);
        printf("Serial Number: %d\n", laptops[i].serial_number);
        printf("Problem: %s\n", laptops[i].problem);
    }
}

void save_laptops() {
    FILE *fp;
    fp = fopen("laptops.txt", "w");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    for (i = 0; i < num_laptops; i++) {
        fprintf(fp, "%s, %s, %d, %s\n", laptops[i].brand, laptops[i].model, laptops[i].serial_number, laptops[i].problem);
    }

    fclose(fp);

    printf("Laptops saved to file.\n");
}

void load_laptops() {
    FILE *fp;
    fp = fopen("laptops.txt", "r");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    num_laptops = 0;

    while (fscanf(fp, "%s %s %d %s", laptops[num_laptops].brand, laptops[num_laptops].model, &laptops[num_laptops].serial_number, laptops[num_laptops].problem) == 4) {
        num_laptops++;
    }

    fclose(fp);

    printf("Laptops loaded from file.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add laptop details\n");
        printf("2. Display laptop details\n");
        printf("3. Save laptop details to file\n");
        printf("4. Load laptop details from file\n");
        printf("5. Exit\n");
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
                save_laptops();
                break;
            case 4:
                load_laptops();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
            }
        }
    }
