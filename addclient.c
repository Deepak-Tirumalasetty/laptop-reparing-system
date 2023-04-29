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

   fprintf(fp, "%s,%s,%s,%s,%s,%s\n", c->name, c->address, c->phone, c->laptop_brand, c->laptop_model, c->issue);
   fclose(fp);

   printf("\nRecord added successfully!\n");
}

int main() {
   struct client c;
   addRecord(&c);
   return 0;
}
