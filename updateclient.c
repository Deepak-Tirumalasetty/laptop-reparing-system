#include<stdio.h>
#include<string.h>

struct client {
   char name[50];
   char address[100];
   char phone[20];
   char laptop_brand[50];
   char laptop_model[50];
   char issue[200];
};
void addRecord(struct client *c) {
   FILE *fp;
   fp = fopen("client_records.txt", "a"); // open file in append mode
   if (fp == NULL) {
      printf("Error: could not open file for writing.\n");
      return;
   }

   printf("Enter client name: ");
   scanf("%s", c->name);
   printf("\nEnter client address: \n");
   scanf("%s", c->address);
   printf("\nEnter client phone number: ");
   scanf("%s", c->phone);
   printf("\nEnter laptop brand: ");
   scanf("%s", c->laptop_brand);
   printf("\nEnter laptop model: ");
   scanf("%s", c->laptop_model);
   printf("\nEnter laptop issue: ");
   scanf("%s", c->issue);

   fprintf(fp, "%s, %s, %s, %s, %s, %s\n", c->name, c->address, c->phone, c->laptop_brand, c->laptop_model, c->issue);
   fclose(fp);

   printf("\nRecord added successfully!\n");
}

void updateRecord(char *name) {
   FILE *fp;
  char tempName[50];
    FILE *tempFile;
   char address[100];
   char phone[20];
   char laptop_brand[50];
   char laptop_model[50];
   char issue[200];
   int found = 0;

   fp = fopen("client_records.txt", "r"); // open file in read mode
   tempFile = fopen("temp.txt", "w"); // create a temporary file for writing
   if (fp == NULL || tempFile == NULL) {
      printf("Error: could not open file.\n");
      return;
   }

   while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", tempName, address, phone, laptop_brand, laptop_model, issue) != EOF) {
      if (strcmp(name, tempName) == 0) {
         found = 1;
         printf("Enter new address: ");
         scanf("%s", address);
         printf("\nEnter new phone number: ");
         scanf("%s", phone);
         printf("\nEnter new laptop brand: ");
         scanf("%s", laptop_brand);
         printf("\nEnter new laptop model: ");
         scanf("%s", laptop_model);
         printf("\nEnter new laptop issue: ");
         scanf("%s", issue);

         fprintf(tempFile, "%s,%s,%s,%s,%s,%s\n", tempName, address, phone, laptop_brand, laptop_model, issue);
         printf("\nRecord updated successfully!\n");
      } else {
         fprintf(tempFile, "%s,%s,%s,%s,%s,%s\n", tempName, address, phone, laptop_brand, laptop_model, issue);
      }
   }

   fclose(fp);
   fclose(tempFile);

   if (!found) {
      printf("Error: record not found.\n");
      remove("temp.txt");
      return;
   }

   remove("client_records.txt");
   rename("temp.txt", "client_records.txt");
}
void deleteRecord(char *name) {
    FILE *fp1, *fp2;
    struct client c;
    fp1 = fopen("client_records.txt", "r");
    fp2 = fopen("temp.txt", "w");
    if (fp1 == NULL || fp2 == NULL) {
        printf("Error: could not open file for reading or writing.\n");
        return;
    }
    int found = 0;
    while (fscanf(fp1, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", c.name, c.address, c.phone, c.laptop_brand, c.laptop_model, c.issue) != EOF) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
        } else {
            fprintf(fp2, "%s,%s,%s,%s,%s,%s\n", c.name, c.address, c.phone, c.laptop_brand, c.laptop_model, c.issue);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if (found) {
        remove("client_records.txt");
        rename("temp.txt", "client_records.txt");
        printf("Record for %s deleted successfully!\n", name);
    } else {
        remove("temp.txt");
        printf("Record not found.\n");
    }
}


int main() {
	struct client c;
    int choice;
    while (1) {
        printf("Choose an option:\n");
        printf("1. Add client\n");
        printf("2. Update client\n");
        printf("3. Delete client\n");
        //printf("4. Print clients\n");
    	printf("4. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
        	case 1:
        		addRecord(&c);
            case 2:
                updateRecord(&c.name);
                break;
            case 3:
                deleteRecord(&c.name);
                break;
            case 4:
            	exit(0);
            default:
                printf("Error: Invalid choice.\n");
                break;
        }
    }
    return (0);
}
